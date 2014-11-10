#include "symbol.h"

typedef struct TY_type_ *TY_type_;
typedef struct TY_type_list_ *TY_type_list;
typedef struct TY_field_ *TY_field;
typedef struct TY_field_ist_ *TY_field_list;

struct TY_type_
{
	enum { TY_RECORD, TY_NIL, TY_INT, TY_STRING, TY_ARRAY, TY_NAME, TY_VOID } kind;
	union
	{
		TY_field_list record;
		TY_type array;
		struct { S_symbol sym; TY_ty type; } name;
	} u;
};

struct TY_type_list_ { TY_type head; TY_type_list tail; };
struct TY_field_ { S_symbol name; TY_type type; };
struct TY_field_list_ { TY_field head; TY_field_list tail; };

TY_type TY_Nil(void);
TY_type TY_Int(void);
TY_type TY_String(void);
TY_type TY_Void(void);

TY_type TY_Record(TY_field_list fields);
TY_type TY_Array(TY_type type);
TY_type TY_Name(S_symbol sym, TY_type type);

TY_type_list TY_Type_list(TY_type head, TY_type_list tail);
TY_field TY_Field(S_symbol name, TY_type type);
TY_field_list TY_Field_list(TY_field head, TY_field_list tail);

void TY_print(TY_type t);
void TY_list_print(TY_type_list list);