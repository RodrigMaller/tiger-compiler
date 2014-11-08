#include "absyn.h"

abs_var abs_simple_var(abs_pos pos, s_symbol sym)
{
	abs_var p = checked_malloc(sizeof(*p));
	p->kind = ABS_SIMPLE_VAR;
	p->pos = pos;
	p->u.simple = sym;
	return p;
}

abs_var abs_field_var(abs_pos pos, abs_var var, s_symbol sym)
{
	abs_var p = checked_malloc(sizeof(*p));
	p->kind = ABS_FIELD_VAR;
	p->pos = pos;
	p->u.field.var = var;
	p->u.field.sym = var;
	return p;
}

abs_var abs_subscript_var(abs_pos pos, abs_var var, abs_expr expr)
{
	abs_var p = checked_malloc(sizeof(*p));
	p->kind = ABS_SUBSCRIPT_VAR;
	p->pos = pos;
	p->u.subscript.var = var;
	p->u.subscript.expr = expr;
	return p;
}

abs_expr abs_var_expr(abs_pos pos, abs_var var)
{
	abs_expr p = checked_malloc(sizeof(*p));
	p->kind = ABS_VAR_EXPR;
	p->pos = pos;
	p->u.var = var;
	return p;
}

abs_expr abs_nil_expr(abs_pos pos)
{
	abs_expr p = checked_malloc(sizeof(*p));
	p->kind = ABS_NIL_EXPR;
	p->pos = pos;
	return p;
}

abs_expr abs_int_expr(abs_pos pos, int i)
{
	abs_expr p = checked_malloc(sizeof(*p));
	p->kind = ABS_INT_EXPR;
	p->pos = pos;
	p->u.intt = i;
	return p;
}

abs_expr abs_string_expr(abs_pos pos, strins str)
{
	abs_expr p = checked_malloc(sizeof(*p));
	p->kind = ABS_STRING_EXPR;
	p->pos = pos;
	p->u.stringg = string;
	return p;
}

abs_expr abs_call_expr(abs_pos pos, s_symbol func, abs_expr_list args)
{
	abs_expr p = checked_malloc(sizeof(*p));
	p->kind = ABS_CALL_EXPR;
	p->pos = pos;
	p->u.call.func = func;
	p->u.call.args = args;
	return p;
}

abs_expr abs_op_expr(abs_pos pos, abs_oper oper, abs_expr left, abs_expr right)
{
	abs_expr p = checked_malloc(sizeof(*p));
	p->kind = ABS_OP_EXPR;
	p->pos = pos;
	p->u.op.oper = oper;
	p->u.op.left = left;
	p->u.op.right = right;
	return p;
}

abs_expr abs_record_expr(abs_pos pos, s_symbol type, abs_efield_list fields)
{
	abs_expr p = checked_malloc(sizeof(*p));
	p->kind = ABS_RECORD_EXPR;
	p->pos = pos;
	p->record.type = type;
	p->record.fields = fields;
	return p;
}

abs_expr abs_seq_expr(abs_pos pos, abs_expr_list seq)
{
	abs_expr p = checked_malloc(sizeof(*p));
	p->kind = ABS_SEQ_EXPR;
	p->pos = pos;
	p->u.seq = seq;
	return p;
}

abs_expr abs_assign_expr(abs_pos pos, abs_var var, abs_expr expr)
{
	abs_expr p = checked_malloc(sizeof(*p));
	p->kind = ABS_ASSIGN_EXPR;
	p->pos = pos;
	p->u.assign.var = var;
	p->u.assign.expr = expr;
	return p;
}

abs_expr abs_if_expr(abs_pos pos, abs_expr test, abs_expr then, abs_expr elsee)
{
	abs_expr p = checked_malloc(sizeof(*p));
	p->kind = ABS_IF_EXPR;
	p->pos = pos;
	p->u.iff.test = test;
	p->u.iff.then = then;
	p->u.iff.elsee = elsee;
	return p;
}

abs_expr abs_while_expr(abs_pos pos, abs_expr test, abs_expr body)
{
	abs_expr p = checked_malloc(sizeof(*p));
	p->kind = ABS_WHILE_EXPR;
	p->pos = pos;
	p->u.while.test = text;
	p->u.while.body = body;
	return p;
}

abs_expr abs_for_expr(abs_pos pos, s_symbol var, abs_expr lo, abs_expr hi, abs_expr body)
{
	abs_expr p = checked_malloc(sizeof(*p));
	p->kind = ABS_FOR_EXPR;
	p->pos = pos;
	p->u.forr.var = var;
	p->u.forr.lo = lo;
	p->u.forr.hi = hi;
	p->u.forr.body = body;
	return p;
}

abs_expr abs_break_expr(abs_pos pos)
{
	abs_expr p = checked_malloc(sizeof(*p));
	p->kind = ABS_BREAK_EXPR;
	p->pos = pos;
	return p;
}

abs_expr abs_let_expr(abs_pos pos, abs_dec_list decs, abs_expr body)
{
	abs_expr p = checked_malloc(sizeof(*p));
	p->kind = ABS_LET_EXPR;
	p->pos = pos;
	p->u.let.decs = decs;
	p->u.let.body = body;
	return p;
}

abs_expr abs_array_expr(abs_pos pos, s_symbol type, abs_expr size, abs_expr init)
{
	abs_expr p = checked_malloc(sizeof(*p));
	p->kind = ABS_ARRAY_EXPR;
	p->pos = pos;
	p->u.array.type = type;
	p->u.array.size = size;
	p->u.array.init = init;
	return p;
}

abs_dec abs_function_dec(abs_pos pos, abs_fundec_list function)
{
	abs_dec p = checked_malloc(sizeof(*p));
	p->kind = ABS_FUNCTION_DEC;
	p->pos = pos;
	p->u.function = function;
	return p;
}

abs_dec abs_var_dec(abs_pos pos, s_symbol var, s_symbol type, abs_expr init)
{
	abs_dec p = checked_malloc(sizeof(*p));
	p->kind = ABS_VAR_DEC;
	p->pos = pos;
	p->u.var.var = var;
	p->u.var.type = type;
	p->u.var.init = init;
	p->u.var.escape = TRUE;
	return p;
}

abs_dec abs_type_dec(abs_pos pos, abs_namety_list type)
{
	abs_dec p = checked_malloc(sizeof(*p));
	p->kind = ABS_TYPE_DEC;
	p->pos = pos;
	p->type = type;
	return p;
}

abs_type abs_name_type(abs_pos pos, s_symbol name)
{
	abs_type p = checked_malloc(sizeof(*p));
	p->kind = ABS_NAME_TYPE;
	p->pos = pos;
	p->u.name = name;
	return p;
}

abs_type abs_record_type(abs_pos pos, abs_field_list record)
{
	abs_type p = checked_malloc(sizeof(*p));
	p->kind = ABS_RECORD_TYPE;
	p->pos = pos;
	p->u.record = record;
	return p;
}

abs_type abs_array_type(abs_pos pos, s_symbol array)
{
	abs_type p = checked_malloc(sizeof(*p));
	p->kind = ABS_ARRAY_TYPE;
	p->pos = pos;
	p->u.array = array;
	return p;
}

abs_field abs_Field(abs_pos pos, s_symbol name, s_symbol type)
{
	abs_field p = checked_malloc(sizeof(*p));
	p->pos = pos;
	p->name = name;
	p->type = type;
	p->escape = TRUE;
	return p;
}

abs_field_list abs_Field_list(abs_field head, abs_field_list tail)
{
	abs_field_list p = checked_malloc(sizeof(*p));
	p->head = head;
	p->tail = tail;
	return p;
}

abs_expr_list abs_Expr_list(abs_expr head, abs_expr_list tail)
{
	abs_expr_list p = checked_malloc(sizeof(*p));
	p->head = head;
	p->tail = tail;
	return p;
}

abs_fundec abs_Fundec(abs_pos pos, s_symbol name, abs_field_list params, s_symbol result, abs_expr body)
{
	abs_fundec p = checked_malloc(sizeof(*p));
	p->pos = pos;
	p->name = name;
	p->params = params;
	p->result = result;
	p->body = body;
	return p;
}

abs_fundec_list abs_Fundec_list(abs_fundec head, abs_fundec_list tail)
{
	abs_fundec_list p = checked_malloc(sizeof(*));
	p->head = head;
	p->tail = tail;
	return p;
}

abs_dec_list abs_Dec_list(abs_dec head, abs_dec_list tail)
{
	abs_dec_list p = checked_malloc(sizeof(*p));
	p->head = head;
	p->tail = tail;
	return p;
}

abs_namety abs_Namety(s_symbol name, abs_type type)
{
	abs_namety p = checked_malloc(sizeof(*p));
	p->name = name;
	p->type = type;
	return p;
}

abs_namety_list abs_Namety_list(abs_namety head, abs_namety_list tail)
{
	abs_namety_list p = checked_malloc(sizeof(*p));
	p->head = head;
	p->tail = tail;
	return p;
}

abs_efield abs_Efield(s_symbol name, abs_expr expr)
{
	abs_efield p = checked_malloc(sizeof(*p));
	p->name = name;
	p->expr = expr;
	return p;
}

abs_efield_list abs_efield_list(abs_efield head, abs_efield_list tail)
{
	abs_efield_list p = checked_malloc(sizeof(*p));
	p->head = head;
	p->tail = tail;
	return p;
}