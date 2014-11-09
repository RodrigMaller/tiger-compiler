#include "ABSyn.h"

ABS_var ABS_simple_var(ABS_pos pos, S_symbol sym)
{
	ABS_var p = checked_malloc(sizeof(*p));
	p->kind = ABS_SIMPLE_VAR;
	p->pos = pos;
	p->u.simple = sym;
	return p;
}

ABS_var ABS_field_var(ABS_pos pos, ABS_var var, S_symbol sym)
{
	ABS_var p = checked_malloc(sizeof(*p));
	p->kind = ABS_FIELD_VAR;
	p->pos = pos;
	p->u.field.var = var;
	p->u.field.sym = var;
	return p;
}

ABS_var ABS_subscript_var(ABS_pos pos, ABS_var var, ABS_expr expr)
{
	ABS_var p = checked_malloc(sizeof(*p));
	p->kind = ABS_SUBSCRIPT_VAR;
	p->pos = pos;
	p->u.subscript.var = var;
	p->u.subscript.expr = expr;
	return p;
}

ABS_expr ABS_var_expr(ABS_pos pos, ABS_var var)
{
	ABS_expr p = checked_malloc(sizeof(*p));
	p->kind = ABS_VAR_EXPR;
	p->pos = pos;
	p->u.var = var;
	return p;
}

ABS_expr ABS_nil_expr(ABS_pos pos)
{
	ABS_expr p = checked_malloc(sizeof(*p));
	p->kind = ABS_NIL_EXPR;
	p->pos = pos;
	return p;
}

ABS_expr ABS_int_expr(ABS_pos pos, int i)
{
	ABS_expr p = checked_malloc(sizeof(*p));
	p->kind = ABS_INT_EXPR;
	p->pos = pos;
	p->u.intt = i;
	return p;
}

ABS_expr ABS_string_expr(ABS_pos pos, strins str)
{
	ABS_expr p = checked_malloc(sizeof(*p));
	p->kind = ABS_STRING_EXPR;
	p->pos = pos;
	p->u.stringg = string;
	return p;
}

ABS_expr ABS_call_expr(ABS_pos pos, S_symbol func, ABS_expr_list args)
{
	ABS_expr p = checked_malloc(sizeof(*p));
	p->kind = ABS_CALL_EXPR;
	p->pos = pos;
	p->u.call.func = func;
	p->u.call.args = args;
	return p;
}

ABS_expr ABS_op_expr(ABS_pos pos, ABS_oper oper, ABS_expr left, ABS_expr right)
{
	ABS_expr p = checked_malloc(sizeof(*p));
	p->kind = ABS_OP_EXPR;
	p->pos = pos;
	p->u.op.oper = oper;
	p->u.op.left = left;
	p->u.op.right = right;
	return p;
}

ABS_expr ABS_record_expr(ABS_pos pos, S_symbol type, ABS_efield_list fields)
{
	ABS_expr p = checked_malloc(sizeof(*p));
	p->kind = ABS_RECORD_EXPR;
	p->pos = pos;
	p->record.type = type;
	p->record.fields = fields;
	return p;
}

ABS_expr ABS_seq_expr(ABS_pos pos, ABS_expr_list seq)
{
	ABS_expr p = checked_malloc(sizeof(*p));
	p->kind = ABS_SEQ_EXPR;
	p->pos = pos;
	p->u.seq = seq;
	return p;
}

ABS_expr ABS_assign_expr(ABS_pos pos, ABS_var var, ABS_expr expr)
{
	ABS_expr p = checked_malloc(sizeof(*p));
	p->kind = ABS_ASSIGN_EXPR;
	p->pos = pos;
	p->u.assign.var = var;
	p->u.assign.expr = expr;
	return p;
}

ABS_expr ABS_if_expr(ABS_pos pos, ABS_expr test, ABS_expr then, ABS_expr elsee)
{
	ABS_expr p = checked_malloc(sizeof(*p));
	p->kind = ABS_IF_EXPR;
	p->pos = pos;
	p->u.iff.test = test;
	p->u.iff.then = then;
	p->u.iff.elsee = elsee;
	return p;
}

ABS_expr ABS_while_expr(ABS_pos pos, ABS_expr test, ABS_expr body)
{
	ABS_expr p = checked_malloc(sizeof(*p));
	p->kind = ABS_WHILE_EXPR;
	p->pos = pos;
	p->u.while.test = text;
	p->u.while.body = body;
	return p;
}

ABS_expr ABS_for_expr(ABS_pos pos, S_symbol var, ABS_expr lo, ABS_expr hi, ABS_expr body)
{
	ABS_expr p = checked_malloc(sizeof(*p));
	p->kind = ABS_FOR_EXPR;
	p->pos = pos;
	p->u.forr.var = var;
	p->u.forr.lo = lo;
	p->u.forr.hi = hi;
	p->u.forr.body = body;
	return p;
}

ABS_expr ABS_break_expr(ABS_pos pos)
{
	ABS_expr p = checked_malloc(sizeof(*p));
	p->kind = ABS_BREAK_EXPR;
	p->pos = pos;
	return p;
}

ABS_expr ABS_let_expr(ABS_pos pos, ABS_dec_list decs, ABS_expr body)
{
	ABS_expr p = checked_malloc(sizeof(*p));
	p->kind = ABS_LET_EXPR;
	p->pos = pos;
	p->u.let.decs = decs;
	p->u.let.body = body;
	return p;
}

ABS_expr ABS_array_expr(ABS_pos pos, S_symbol type, ABS_expr size, ABS_expr init)
{
	ABS_expr p = checked_malloc(sizeof(*p));
	p->kind = ABS_ARRAY_EXPR;
	p->pos = pos;
	p->u.array.type = type;
	p->u.array.size = size;
	p->u.array.init = init;
	return p;
}

ABS_dec ABS_function_dec(ABS_pos pos, ABS_fundec_list function)
{
	ABS_dec p = checked_malloc(sizeof(*p));
	p->kind = ABS_FUNCTION_DEC;
	p->pos = pos;
	p->u.function = function;
	return p;
}

ABS_dec ABS_var_dec(ABS_pos pos, S_symbol var, S_symbol type, ABS_expr init)
{
	ABS_dec p = checked_malloc(sizeof(*p));
	p->kind = ABS_VAR_DEC;
	p->pos = pos;
	p->u.var.var = var;
	p->u.var.type = type;
	p->u.var.init = init;
	p->u.var.escape = TRUE;
	return p;
}

ABS_dec ABS_type_dec(ABS_pos pos, ABS_namety_list type)
{
	ABS_dec p = checked_malloc(sizeof(*p));
	p->kind = ABS_TYPE_DEC;
	p->pos = pos;
	p->type = type;
	return p;
}

ABS_type ABS_name_type(ABS_pos pos, S_symbol name)
{
	ABS_type p = checked_malloc(sizeof(*p));
	p->kind = ABS_NAME_TYPE;
	p->pos = pos;
	p->u.name = name;
	return p;
}

ABS_type ABS_record_type(ABS_pos pos, ABS_field_list record)
{
	ABS_type p = checked_malloc(sizeof(*p));
	p->kind = ABS_RECORD_TYPE;
	p->pos = pos;
	p->u.record = record;
	return p;
}

ABS_type ABS_array_type(ABS_pos pos, S_symbol array)
{
	ABS_type p = checked_malloc(sizeof(*p));
	p->kind = ABS_ARRAY_TYPE;
	p->pos = pos;
	p->u.array = array;
	return p;
}

ABS_field ABS_Field(ABS_pos pos, S_symbol name, S_symbol type)
{
	ABS_field p = checked_malloc(sizeof(*p));
	p->pos = pos;
	p->name = name;
	p->type = type;
	p->escape = TRUE;
	return p;
}

ABS_field_list ABS_Field_list(ABS_field head, ABS_field_list tail)
{
	ABS_field_list p = checked_malloc(sizeof(*p));
	p->head = head;
	p->tail = tail;
	return p;
}

ABS_expr_list ABS_Expr_list(ABS_expr head, ABS_expr_list tail)
{
	ABS_expr_list p = checked_malloc(sizeof(*p));
	p->head = head;
	p->tail = tail;
	return p;
}

ABS_fundec ABS_Fundec(ABS_pos pos, S_symbol name, ABS_field_list params, S_symbol result, ABS_expr body)
{
	ABS_fundec p = checked_malloc(sizeof(*p));
	p->pos = pos;
	p->name = name;
	p->params = params;
	p->result = result;
	p->body = body;
	return p;
}

ABS_fundec_list ABS_Fundec_list(ABS_fundec head, ABS_fundec_list tail)
{
	ABS_fundec_list p = checked_malloc(sizeof(*));
	p->head = head;
	p->tail = tail;
	return p;
}

ABS_dec_list ABS_Dec_list(ABS_dec head, ABS_dec_list tail)
{
	ABS_dec_list p = checked_malloc(sizeof(*p));
	p->head = head;
	p->tail = tail;
	return p;
}

ABS_namety ABS_Namety(S_symbol name, ABS_type type)
{
	ABS_namety p = checked_malloc(sizeof(*p));
	p->name = name;
	p->type = type;
	return p;
}

ABS_namety_list ABS_Namety_list(ABS_namety head, ABS_namety_list tail)
{
	ABS_namety_list p = checked_malloc(sizeof(*p));
	p->head = head;
	p->tail = tail;
	return p;
}

ABS_efield ABS_Efield(S_symbol name, ABS_expr expr)
{
	ABS_efield p = checked_malloc(sizeof(*p));
	p->name = name;
	p->expr = expr;
	return p;
}

ABS_efield_list ABS_efield_list(ABS_efield head, ABS_efield_list tail)
{
	ABS_efield_list p = checked_malloc(sizeof(*p));
	p->head = head;
	p->tail = tail;
	return p;
}