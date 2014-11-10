#include <assert.h>
#include <stdio.h>

#include "utils.h"
#include "types.h"

static struct TY_type_ ty_nil = { TY_NIL };
TY_type TY_Nil(void)
{
	return &ty_nil;
}

static struct TY_type_ ty_int = { TY_INT };
TY_type TY_Int(void)
{
	return &ty_int;
}

static struct TY_type_ ty_string = { TY_STRING };
TY_type TY_String(void)
{
	return &ty_string;
}

static struct TY_type_ ty_void = { TY_VOID };
TY_type TY_Void(void)
{
	return &ty_void;
}

TY_type TY_Record(TY_field_list fields)
{
	TY_type p = checked_malloc(sizeof(*p));
	p->kind = TY_RECORD;
	p->u.record = fields;
	return p;
}

TY_type TY_Array(TY_type type)
{
	TY_type p = checked_malloc(sizeof(*p));
	p->kind = TY_ARRAY;
	p->u.array = type;
	return p;
}

TY_type TY_Name(S_symbol sym, TY_type type)
{
	TY_type p = checked_malloc(sizeof(*p));
	p->kind = TY_NAME;
	p->u.name.sym = sym;
	p->u.name.type = type;
	return p;
}

TY_type_list TY_Type_list(TY_type head, TY_type_list tail)
{
	TY_type_list p = checked_malloc(sizeof(*p));
	p->head = head;
	p->tail = tail;
	return p;
}

TY_field TY_Field(S_symbol name, TY_type type)
{
	TY_field p = checked_malloc(sizeof(*p));
	p->name = name;
	p->type = type;
	return p;
}

TY_field_list TY_Field_list(TY_field head, TY_field_list tail)
{
	TY_field_list p = checked_malloc(sizeof(*p));
	p->head = head;
	p->tail = tail;
	return p;
}

static char ty_str[][12] = {
	"ty_record", "ty_nil", "ty_int", "ty_string",
	"ty_array", "ty_name", "ty_void"
};

void TY_print(TY_type t)
{
	if (t == NULL) printf("null");
	else
	{
		printf("%s", str_ty[t->kind]);
		if (t->kind == TY_NAME)
		{
			printf(", %s", S_name(t->u.name.sym));
		}
	}
}

void TY_list_print(TY_type_list list)
{
	if (list == NULL) printf("null");
	else
	{
		printf("type_list(");
		TY_print(list->head);
		printf(", ");
		TY_list_print(list->tail);
		printf(")");
	}
}