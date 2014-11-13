#include "symbol.h"

typedef int ABS_pos;

typedef struct ABS_var_ *ABS_var;
typedef struct ABS_expr_ *ABS_expr;
typedef struct ABS_dec_ *ABS_dec;
typedef struct ABS_type_ *ABS_type;

typedef struct ABS_dec_list_ *ABS_dec_list;
typedef struct ABS_expr_list_ *ABS_expr_list;
typedef struct ABS_field_ *ABS_field;
typedef struct ABS_field_list_ *ABS_field_list;
typedef struct ABS_fundec_ *ABS_fundec;
typedef struct ABS_fundec_list_ *ABS_fundec_list;
typedef struct ABS_namety_ *ABS_namety;
typedef struct ABS_namety_list_ *ABS_namety_list;
typedef struct ABS_efield_ *ABS_efield;
typedef struct ABS_efield_list_ *ABS_efield_list;

typedef enum
{  
    ABS_PLUS, ABS_MINUS, ABS_TIMES, ABS_DIVIDE,
    ABS_EQ, ABS_NEQ, ABS_LT, ABS_LE, ABS_GT, ABS_GE,
} ABS_oper;

struct ABS_var_
{
    enum { ABS_SIMPLE_VAR, ABS_FIELD_VAR, ABS_SUBSCRIPT_VAR } kind;
    ABS_pos pos;
    union 
    {
        S_symbol simple;
        struct { ABS_var var; S_symbol sym; } field;
        struct { ABS_var var; ABS_expr expr; } subscript;
    } u;
};

struct ABS_expr_
{
    enum 
    {
        ABS_VAR_EXPR, ABS_NIL_EXPR, ABS_INT_EXPR, ABS_STRING_EXPR,
        ABS_CALL_EXPR, ABS_OP_EXPR, ABS_RECORD_EXPR, ABS_SEQ_EXPR,
        ABS_ASSIGN_EXPR, ABS_IF_EXPR, ABS_WHILE_EXPR, ABS_FOR_EXPR,
        ABS_BREAK_EXPR, ABS_LET_EXPR, ABS_ARRAY_EXPR
    } kind;
    ABS_pos pos;
    union
    {
        ABS_var var;
        /* nil; */
        int intt;
        string stringg;
        struct { S_symbol func; ABS_expr_list args; } call;
        struct { ABS_oper oper; ABS_expr left; ABS_expr right; } op;
        struct { S_symbol type; ABS_efield_list fields; } recordd;
        ABS_expr_list seq;
        struct { ABS_var var; ABS_expr expr; } assign;
        struct { ABS_expr test, then, elsee; } iff;
        struct { ABS_expr test, body; } whilee;
        struct { S_symbol var; ABS_expr lo, hi, body; bool escape; } forr;
        /* breakk; */
        struct { ABS_dec_list decs; ABS_expr body; } let;
        struct { S_symbol type; ABS_expr size, init; } array;
    } u;
};

struct ABS_dec_
{
    enum { ABS_FUNCTION_DEC, ABS_VAR_DEC, ABS_TYPE_DEC } kind;
    ABS_pos pos;
    union 
    {
        ABS_fundec_list function;
        struct { S_symbol var; S_symbol type; ABS_expr init; bool escape; } var;
        ABS_namety_list type;
    } u;
};

struct ABS_type_
{
    enum { ABS_NAME_TYPE, ABS_RECORD_TYPE, ABS_ARRAY_TYPE } kind;
    ABS_pos pos;
    union
    {
        S_symbol name;
        ABS_field_list record;
        S_symbol array;
    } u;
};

struct ABS_field_             { S_symbol name, type; bool escape; };
struct ABS_field_list_        { ABS_field head; ABS_field_list tail; };
struct ABS_efield_            { ABS_pos pos; S_symbol name; ABS_expr expr; };
struct ABS_efield_list_       { ABS_efield head; ABS_efield_list tail; };
struct ABS_expr_list_         { ABS_expr head; ABS_expr_list tail; };
struct ABS_fundec_            { ABS_pos pos; S_symbol name; ABS_field_list params; S_symbol result; ABS_expr body; };
struct ABS_fundec_list_       { ABS_fundec head; ABS_fundec_list tail; };
struct ABS_dec_list_          { ABS_dec head; ABS_dec_list tail; };
struct ABS_namety_            { S_symbol name; ABS_type type; };
struct ABS_namety_list_       { ABS_namety head; ABS_namety_list tail; };

ABS_var          ABS_simple_var(ABS_pos pos, S_symbol sym);
ABS_var          ABS_field_var(ABS_pos pos, ABS_var var, S_symbol sym);
ABS_var          ABS_subscript_var(ABS_pos pos, ABS_var var, ABS_expr expr);
ABS_expr         ABS_var_expr(ABS_pos pos, ABS_var var);
ABS_expr         ABS_nil_expr(ABS_pos pos);
ABS_expr         ABS_int_expr(ABS_pos pos, int i);
ABS_expr         ABS_string_expr(ABS_pos pos, string str);
ABS_expr         ABS_call_expr(ABS_pos pos, S_symbol func, ABS_expr_list args);
ABS_expr         ABS_op_expr(ABS_pos pos, ABS_oper oper, ABS_expr left, ABS_expr right);
ABS_expr         ABS_record_expr(ABS_pos pos, S_symbol type, ABS_efield_list fields);
ABS_expr         ABS_seq_expr(ABS_pos pos, ABS_expr_list seq);
ABS_expr         ABS_assign_expr(ABS_pos pos, ABS_var var, ABS_expr expr);
ABS_expr         ABS_if_expr(ABS_pos pos, ABS_expr test, ABS_expr then, ABS_expr elsee);
ABS_expr         ABS_while_expr(ABS_pos pos, ABS_expr test, ABS_expr body);
ABS_expr         ABS_for_expr(ABS_pos pos, S_symbol var, ABS_expr lo, ABS_expr hi, ABS_expr body);
ABS_expr         ABS_break_expr(ABS_pos pos);
ABS_expr         ABS_let_expr(ABS_pos pos, ABS_dec_list decs, ABS_expr body);
ABS_expr         ABS_array_expr(ABS_pos pos, S_symbol type, ABS_expr size, ABS_expr init);
ABS_dec          ABS_function_dec(ABS_pos pos, ABS_fundec_list function);
ABS_dec          ABS_var_dec(ABS_pos pos, S_symbol var, S_symbol type, ABS_expr init);
ABS_dec          ABS_type_dec(ABS_pos pos, ABS_namety_list type);
ABS_type         ABS_name_type(ABS_pos pos, S_symbol name);
ABS_type         ABS_record_type(ABS_pos pos, ABS_field_list record);
ABS_type         ABS_array_type(ABS_pos pos, S_symbol array);
ABS_field        ABS_Field(S_symbol name, S_symbol type);
ABS_field_list   ABS_Field_list(ABS_field head, ABS_field_list tail);
ABS_expr_list    ABS_Expr_list(ABS_expr head, ABS_expr_list tail);
ABS_fundec       ABS_Fundec(ABS_pos pos, S_symbol name, ABS_field_list params, S_symbol result, ABS_expr body);
ABS_fundec_list  ABS_Fundec_list(ABS_fundec head, ABS_fundec_list tail);
ABS_dec_list     ABS_Dec_list(ABS_dec head, ABS_dec_list tail);
ABS_namety       ABS_Namety(S_symbol name, ABS_type type);
ABS_namety_list  ABS_Namety_list(ABS_namety head, ABS_namety_list tail);
ABS_efield       ABS_Efield(ABS_pos pos, S_symbol name, ABS_expr expr);
ABS_efield_list  ABS_Efield_list(ABS_efield head, ABS_efield_list tail);
