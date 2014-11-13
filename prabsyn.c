#include <assert.h>

#include "prabsyn.h"

static void pr_var(FILE *fp, ABS_var v, int d);
static void pr_dec(FILE *fp, ABS_dec v, int d);
static void pr_type(FILE *fp, ABS_type v, int d);
static void pr_field(FILE *fp, ABS_field v, int d);
static void pr_field_list(FILE *fp, ABS_field_list v, int d);
static void pr_expr_list(FILE *fp, ABS_expr_list v, int d);
static void pr_fundec(FILE *fp, ABS_fundec v, int d);
static void pr_fundec_list(FILE *fp, ABS_fundec_list v, int d);
static void pr_dec_list(FILE *fp, ABS_dec_list v, int d);
static void pr_namety(FILE *fp, ABS_namety v, int d);
static void pr_namety_list(FILE *fp, ABS_namety_list v, int d);
static void pr_efield(FILE *fp, ABS_efield v, int d);
static void pr_efield_list(FILE *fp, ABS_efield_list v, int d);

static void indent(FILE *fp, int d)
{
    fprintf(fp, "%*s", d+1, " ");
}

static char str_oper[][12] = {
   "PLUS", "MINUS", "TIMES", "DIVIDE", 
   "EQ", "NEQ", "LT", "LE", "GT", "GE"
   "AND", "OR"
};

static void pr_oper(FILE *fp, ABS_oper d)
{
    fprintf(fp, "%s", str_oper[d]);
}

static void pr_var(FILE *fp, ABS_var v, int d)
{
    indent(fp, d);
    switch (v->kind) 
    {
        case ABS_SIMPLE_VAR:
            fprintf(fp, "simple_var(%s)\n", S_name(v->u.simple)); 
            break;
        case ABS_FIELD_VAR:
            fprintf(fp, "field_var(\n");
            pr_var(fp, v->u.field.var, d+1); 
            indent(fp, d+1);
            fprintf(fp, "%s\n", S_name(v->u.field.sym)); 
            indent(fp, d); 
            fprintf(fp, ")\n");
            break;
        case ABS_SUBSCRIPT_VAR:
            fprintf(fp, "subscript_var(\n");
            pr_var(fp, v->u.subscript.var, d+1);
            pr_expr(fp, v->u.subscript.expr, d+1);
            indent(fp, d); 
            fprintf(fp, ")\n");
            break;
        default:
            assert(0); 
    }
}

void pr_expr(FILE *fp, ABS_expr v, int d) {
    indent(fp, d);
    switch (v->kind) 
    {
        case ABS_VAR_EXPR:
            fprintf(fp, "var_expr(\n"); 
            pr_var(fp, v->u.var, d+1);
            indent(fp, d); 
            fprintf(fp, ")\n");
            break;
        case ABS_NIL_EXPR:
            fprintf(fp, "nil_expr()\n");
            break;
        case ABS_INT_EXPR:
            fprintf(fp, "int_expr(%d)\n", v->u.intt);
            break;
        case ABS_STRING_EXPR:
            fprintf(fp, "string_expr(%s)\n", v->u.stringg);
            break;
        case ABS_CALL_EXPR:
            fprintf(fp, "call_expr(%s\n", S_name(v->u.call.func));
            indent(fp, d+1);
            pr_expr_list(fp, v->u.call.args, d+2);
            indent(fp, d);
            fprintf(fp, ")\n");
            break;
        case ABS_OP_EXPR:
            fprintf(fp, "op_expr(\n");
            indent(fp, d+1); 
            pr_oper(fp, v->u.op.oper); 
            pr_expr(fp, v->u.op.left, d+1);
            pr_expr(fp, v->u.op.right, d+1);
            indent(fp, d); 
            fprintf(fp, ")\n");
            break;
        case ABS_RECORD_EXPR:
            fprintf(fp, "record_expr(%s\n", S_name(v->u.recordd.type));
            indent(fp, d+1); 
            pr_efield_list(fp, v->u.recordd.fields, d+2);
            indent(fp, d);
            fprintf(fp, ")\n");
            break;
        case ABS_SEQ_EXPR:
            fprintf(fp, "seq_expr(\n");
            pr_expr_list(fp, v->u.seq, d+1); 
            fprintf(fp, ")\n");
            break;
        case ABS_ASSIGN_EXPR:
            fprintf(fp, "assign_expr(\n");
            pr_var(fp, v->u.assign.var, d+1);
            pr_expr(fp, v->u.assign.expr, d+1);
            indent(fp, d); 
            fprintf(fp, ")\n");
            break;
        case ABS_IF_EXPR:
            fprintf(fp, "iff_expr(\n");
            pr_expr(fp, v->u.iff.test, d+1); 
            pr_expr(fp, v->u.iff.then, d+1);
            if (v->u.iff.elsee) 
            { /* else is optional */
                pr_expr(fp, v->u.iff.elsee, d+1);
            }
            indent(fp, d);
            fprintf(fp, ")\n");
            break;
        case ABS_WHILE_EXPR:
            fprintf(fp, "while_expr(\n");
            pr_expr(fp, v->u.whilee.test, d+1);
            pr_expr(fp, v->u.whilee.body, d+1);
            indent(fp, d); 
            fprintf(fp, ")\n");
            break;
        case ABS_FOR_EXPR:
            fprintf(fp, "for_expr(%s,\n", S_name(v->u.forr.var)); 
            indent(fp, d+1);
            fprintf(fp, "%s\n", v->u.forr.escape ? "TRUE" : "FALSE");
            pr_expr(fp, v->u.forr.lo, d+1); 
            pr_expr(fp, v->u.forr.hi, d+1);
            pr_expr(fp, v->u.forr.body, d+1); 
            indent(fp, d);
            fprintf(fp, ")\n");
            break;
        case ABS_BREAK_EXPR:
            fprintf(fp, "break_expr()\n");
            break;
        case ABS_LET_EXPR:
            fprintf(fp, "let_expr(\n");
            indent(fp, d+1);
            pr_dec_list(fp, v->u.let.decs, d+2);
            pr_expr(fp, v->u.let.body, d+1);
            indent(fp, d);
            fprintf(fp, ")\n");
            break;
        case ABS_ARRAY_EXPR:
            fprintf(fp, "array_expr(%s\n", S_name(v->u.array.type));
            pr_expr(fp, v->u.array.size, d+1);
            pr_expr(fp, v->u.array.init, d+1);
            indent(fp, d); 
            fprintf(fp, ")\n");
            break;
        default:
            assert(0); 
    } 
}

static void pr_dec(FILE *fp, ABS_dec v, int d) {
    indent(fp, d);
    switch (v->kind) 
    {
        case ABS_FUNCTION_DEC:
            fprintf(fp, "function_dec(\n"); 
            pr_fundec_list(fp, v->u.function, d+1);
            fprintf(fp, ")\n");
            break;
        case ABS_VAR_DEC:
            fprintf(fp, "var_dec(%s\n", S_name(v->u.var.var));
            if (v->u.var.type)
            {
                indent(fp, d+1); 
                fprintf(fp, "%s\n", S_name(v->u.var.type)); 
            }
            pr_expr(fp, v->u.var.init, d+1);
            indent(fp, d+1); 
            fprintf(fp, "%s\n", v->u.var.escape ? "TRUE" : "FALSE");
            indent(fp, d); 
            fprintf(fp, ")\n");
            break;
        case ABS_TYPE_DEC:
            fprintf(fp, "type_dec(\n"); 
            pr_namety_list(fp, v->u.type, d+1); 
            fprintf(fp, ")\n");
            break;
        default:
            assert(0); 
    } 
}

static void pr_type(FILE *fp, ABS_type v, int d) {
    indent(fp, d);
    switch (v->kind) 
    {
        case ABS_NAME_TYPE:
            fprintf(fp, "name_type(%s)\n", S_name(v->u.name));
            break;
        case ABS_RECORD_TYPE:
            fprintf(fp, "record_type(\n");
            pr_field_list(fp, v->u.record, d+1);
            fprintf(fp, ")\n");
            break;
        case ABS_ARRAY_TYPE:
            fprintf(fp, "array_type(%s)\n", S_name(v->u.array));
            break;
        default:
            assert(0);
    } 
}

static void pr_field(FILE *fp, ABS_field v, int d) {
    indent(fp, d);
    fprintf(fp, "field(%s\n", S_name(v->name));
    indent(fp, d+1); 
    fprintf(fp, "%s\n", S_name(v->type));
    indent(fp, d+1); 
    fprintf(fp, "%s\n", v->escape ? "TRUE" : "FALSE");
    indent(fp, d);
    fprintf(fp, ")\n");
}

static void pr_field_list(FILE *fp, ABS_field_list v, int d) {
    indent(fp, d);
    if (v) 
    {
        fprintf(fp, "field_list(\n");
        pr_field(fp, v->head, d+1);
        fprintf(fp, ",\n");
        pr_field_list(fp, v->tail, d+1); 
        fprintf(fp, ")\n");
    }
    else fprintf(fp, "field_list()\n");
}

static void pr_expr_list(FILE *fp, ABS_expr_list v, int d) {
    indent(fp, d);
    if (v) 
    {
        fprintf(fp, "expr_list(\n"); 
        pr_expr(fp, v->head, d+1); 
        fprintf(fp, ",\n");
        pr_expr_list(fp, v->tail, d+1);
        fprintf(fp, ")\n");
    }
    else fprintf(fp, "expr_list()\n"); 
}

static void pr_fundec(FILE *fp, ABS_fundec v, int d) {
    indent(fp, d);
    fprintf(fp, "fundec(%s\n", S_name(v->name));
    pr_field_list(fp, v->params, d+1); 
    fprintf(fp, ",\n");
    if (v->result) 
    {
        indent(fp, d+1); 
        fprintf(fp, "%s,\n", S_name(v->result));
    }
    pr_expr(fp, v->body, d+1); 
    fprintf(fp, ")\n");
}

static void pr_fundec_list(FILE *fp, ABS_fundec_list v, int d) {
    indent(fp, d);
    if (v) 
    {
        fprintf(fp, "fundec_list(\n"); 
        pr_fundec(fp, v->head, d+1); 
        fprintf(fp, ",\n");
        pr_fundec_list(fp, v->tail, d+1); 
        fprintf(fp, ")\n");
    }
    else fprintf(fp, "fundec_list()\n");
}

static void pr_dec_list(FILE *fp, ABS_dec_list v, int d) {
    indent(fp, d);
    if (v) 
    {
        fprintf(fp, "dec_list(\n"); 
        pr_dec(fp, v->head, d+1); 
        fprintf(fp, ",\n");
        pr_dec_list(fp, v->tail, d+1);
        fprintf(fp, ")\n");
    }
    else fprintf(fp, "dec_list()\n"); 
}

static void pr_namety(FILE *fp, ABS_namety v, int d) {
    indent(fp, d);
    fprintf(fp, "namety(%s\n", S_name(v->name)); 
    pr_type(fp, v->type, d+1); 
    fprintf(fp, ")\n");
}

static void pr_namety_list(FILE *fp, ABS_namety_list v, int d) {
    indent(fp, d);
    if (v) 
    {
        fprintf(fp, "namety_list(\n"); 
        pr_namety(fp, v->head, d+1);
        fprintf(fp, ",\n");
        pr_namety_list(fp, v->tail, d+1); 
        fprintf(fp, ")\n");
    }
    else fprintf(fp, "namety_list()\n");
}

static void pr_efield(FILE *fp, ABS_efield v, int d) {
    indent(fp, d);
    if (v) 
    {
        fprintf(fp, "efield(%s\n", S_name(v->name));
        pr_expr(fp, v->expr, d+1); 
        fprintf(fp, ")\n");
    }
    else fprintf(fp, "efield()\n");
}

static void pr_efield_list(FILE *fp, ABS_efield_list v, int d) {
    indent(fp, d);
    if (v) 
    {
        fprintf(fp, "efield_list(\n"); 
        pr_efield(fp, v->head, d+1); 
        fprintf(fp, ",\n");
        pr_efield_list(fp, v->tail, d+1); 
        fprintf(fp, ")");
    }
    else fprintf(fp, "efield_list()");
}
