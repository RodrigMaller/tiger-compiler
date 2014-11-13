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
    fprintf(fp, "%*s", d+2, " ");
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
            fprintf(fp, "simple_var(%s)", S_name(v->u.simple)); 
            break;
        case ABS_FIELD_VAR:
            fprintf(fp, "%s\n", "field_var(");
            pr_var(fp, v->u.field.var, d+2);
            fprintf(fp, "%s\n", ",");
            indent(fp, d+2); 
            fprintf(fp, "%s)", S_name(v->u.field.sym)); 
            break;
        case ABS_SUBSCRIPT_VAR:
            fprintf(fp, "%s\n", "subscript_var(");
            pr_var(fp, v->u.subscript.var, d+2);
            fprintf(fp, "%s\n", ",");
            pr_expr(fp, v->u.subscript.expr, d+2);
            fprintf(fp, "%s", ")");
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
            pr_var(fp, v->u.var, d+2);
            fprintf(fp, "%s", ")");
            break;
        case ABS_NIL_EXPR:
            fprintf(fp, "nil_expr()");
            break;
        case ABS_INT_EXPR:
            fprintf(fp, "int_expr(%d)", v->u.intt);
            break;
        case ABS_STRING_EXPR:
            fprintf(fp, "string_expr(%s)", v->u.stringg);
            break;
        case ABS_CALL_EXPR:
            fprintf(fp, "call_expr(%s\n", S_name(v->u.call.func));
            pr_expr_list(fp, v->u.call.args, d+2);
            fprintf(fp, ")");
            break;
        case ABS_OP_EXPR:
            fprintf(fp, "op_expr(\n");
            indent(fp, d+2);
            pr_oper(fp, v->u.op.oper);
            fprintf(fp, ",\n"); 
            pr_expr(fp, v->u.op.left, d+2);
            fprintf(fp, ",\n");
            pr_expr(fp, v->u.op.right, d+2);
            fprintf(fp, ")");
            break;
        case ABS_RECORD_EXPR:
            fprintf(fp, "record_expr(%s,\n", S_name(v->u.recordd.type));
            pr_efield_list(fp, v->u.recordd.fields, d+2);
            fprintf(fp, ")");
            break;
        case ABS_SEQ_EXPR:
            fprintf(fp, "seq_expr(\n");
            pr_expr_list(fp, v->u.seq, d+2); 
            fprintf(fp, ")\n");
            break;
        case ABS_ASSIGN_EXPR:
            fprintf(fp, "assign_expr(\n");
            pr_var(fp, v->u.assign.var, d+2);
            fprintf(fp, ",\n");
            pr_expr(fp, v->u.assign.expr, d+2);
            fprintf(fp, ")");
            break;
        case ABS_IF_EXPR:
            fprintf(fp, "iff_expr(\n");
            pr_expr(fp, v->u.iff.test, d+2);
            fprintf(fp, ",\n"); 
            pr_expr(fp, v->u.iff.then, d+2);
            if (v->u.iff.elsee) 
            {
                fprintf(fp, ",\n");
                pr_expr(fp, v->u.iff.elsee, d+2);
            }
            fprintf(fp, ")");
            break;
        case ABS_WHILE_EXPR:
            fprintf(fp, "while_expr(\n");
            pr_expr(fp, v->u.whilee.test, d+2);
            fprintf(fp, ",\n");
            pr_expr(fp, v->u.whilee.body, d+2);
            fprintf(fp, ")\n");
            break;
        case ABS_FOR_EXPR:
            fprintf(fp, "for_expr(%s,\n", S_name(v->u.forr.var));
            pr_expr(fp, v->u.forr.lo, d+2);
            fprintf(fp, ",\n");
            pr_expr(fp, v->u.forr.hi, d+2);
            fprintf(fp, ",\n");
            pr_expr(fp, v->u.forr.body, d+2);
            fprintf(fp, ",\n"); 
            indent(fp, d+2);
            fprintf(fp, "%s", v->u.forr.escape ? "TRUE)" : "FALSE)");
            break;
        case ABS_BREAK_EXPR:
            fprintf(fp, "break_expr()");
            break;
        case ABS_LET_EXPR:
            fprintf(fp, "let_expr(\n");
            pr_dec_list(fp, v->u.let.decs, d+2);
            fprintf(fp, ",\n");
            pr_expr(fp, v->u.let.body, d+2);
            fprintf(fp, ")\n");
            break;
        case ABS_ARRAY_EXPR:
            fprintf(fp, "array_expr(%s,\n", S_name(v->u.array.type));
            pr_expr(fp, v->u.array.size, d+2);
            fprintf(fp, ",\n");
            pr_expr(fp, v->u.array.init, d+2);
            fprintf(fp, ")");
            break;
        default:
            assert(0); 
    } 
}

static void pr_dec(FILE *fp, ABS_dec v, int d) 
{
    indent(fp, d);
    switch (v->kind) 
    {
        case ABS_FUNCTION_DEC:
            fprintf(fp, "function_dec(\n"); 
            pr_fundec_list(fp, v->u.function, d+2);
            fprintf(fp, ")");
            break;
        case ABS_VAR_DEC:
            fprintf(fp, "var_dec(%s,\n", S_name(v->u.var.var));
            if (v->u.var.type)
            {
                indent(fp, d+2);
                fprintf(fp, "%s,\n", S_name(v->u.var.type)); 
            }
            pr_expr(fp, v->u.var.init, d+2);
            fprintf(fp, ",\n"); 
            indent(fp, d+2);
            fprintf(fp, "%s", v->u.var.escape ? "TRUE)" : "FALSE)");;
            break;
        case ABS_TYPE_DEC:
            fprintf(fp, "type_dec(\n"); 
            pr_namety_list(fp, v->u.type, d+2); 
            fprintf(fp, ")");
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
            fprintf(fp, "name_type(%s)", S_name(v->u.name));
            break;
        case ABS_RECORD_TYPE:
            fprintf(fp, "record_type(\n");
            pr_field_list(fp, v->u.record, d+2);
            fprintf(fp, ")");
            break;
        case ABS_ARRAY_TYPE:
            fprintf(fp, "array_type(%s)", S_name(v->u.array));
            break;
        default:
            assert(0);
    } 
}

static void pr_field(FILE *fp, ABS_field v, int d) {
    indent(fp, d);
    fprintf(fp, "field(%s,\n", S_name(v->name));
    indent(fp, d+2); 
    fprintf(fp, "%s,\n", S_name(v->type));
    indent(fp, d+2); 
    fprintf(fp, "%s", v->escape ? "TRUE)" : "FALSE)");
}

static void pr_field_list(FILE *fp, ABS_field_list v, int d) {
    indent(fp, d);
    if (v) 
    {
        fprintf(fp, "field_list(\n");
        pr_field(fp, v->head, d+2);
        fprintf(fp, ",\n");
        pr_field_list(fp, v->tail, d+2); 
        fprintf(fp, ")");
    }
    else fprintf(fp, "field_list()");
}

static void pr_expr_list(FILE *fp, ABS_expr_list v, int d) {
    indent(fp, d);
    if (v) 
    {
        fprintf(fp, "expr_list(\n"); 
        pr_expr(fp, v->head, d+2); 
        fprintf(fp, ",\n");
        pr_expr_list(fp, v->tail, d+2);
        fprintf(fp, ")");
    }
    else fprintf(fp, "expr_list()"); 
}

static void pr_fundec(FILE *fp, ABS_fundec v, int d) {
    indent(fp, d);
    fprintf(fp, "fundec(%s,\n", S_name(v->name));
    pr_field_list(fp, v->params, d+2); 
    fprintf(fp, ",\n");
    if (v->result) 
    {
        indent(fp, d+2); 
        fprintf(fp, "%s,\n", S_name(v->result));
    }
    pr_expr(fp, v->body, d+2); 
    fprintf(fp, ")");
}

static void pr_fundec_list(FILE *fp, ABS_fundec_list v, int d) {
    indent(fp, d);
    if (v) 
    {
        fprintf(fp, "fundec_list(\n"); 
        pr_fundec(fp, v->head, d+2); 
        fprintf(fp, ",\n");
        pr_fundec_list(fp, v->tail, d+2); 
        fprintf(fp, ")");
    }
    else fprintf(fp, "fundec_list()");
}

static void pr_dec_list(FILE *fp, ABS_dec_list v, int d) {
    indent(fp, d);
    if (v) 
    {
        fprintf(fp, "dec_list(\n"); 
        pr_dec(fp, v->head, d+2); 
        fprintf(fp, ",\n");
        pr_dec_list(fp, v->tail, d+2);
        fprintf(fp, ")");
    }
    else fprintf(fp, "dec_list()"); 
}

static void pr_namety(FILE *fp, ABS_namety v, int d) {
    indent(fp, d);
    fprintf(fp, "namety(%s,\n", S_name(v->name)); 
    pr_type(fp, v->type, d+2); 
    fprintf(fp, ")");
}

static void pr_namety_list(FILE *fp, ABS_namety_list v, int d) {
    indent(fp, d);
    if (v) 
    {
        fprintf(fp, "namety_list(\n"); 
        pr_namety(fp, v->head, d+2);
        fprintf(fp, ",\n");
        pr_namety_list(fp, v->tail, d+2); 
        fprintf(fp, ")");
    }
    else fprintf(fp, "namety_list()");
}

static void pr_efield(FILE *fp, ABS_efield v, int d) {
    indent(fp, d);
    if (v) 
    {
        fprintf(fp, "efield(%s,\n", S_name(v->name));
        pr_expr(fp, v->expr, d+2); 
        fprintf(fp, ")");
    }
    else fprintf(fp, "efield()");
}

static void pr_efield_list(FILE *fp, ABS_efield_list v, int d) {
    indent(fp, d);
    if (v) 
    {
        fprintf(fp, "efield_list(\n"); 
        pr_efield(fp, v->head, d+2); 
        fprintf(fp, ",\n");
        pr_efield_list(fp, v->tail, d+2); 
        fprintf(fp, ")");
    }
    else fprintf(fp, "efield_list()");
}
