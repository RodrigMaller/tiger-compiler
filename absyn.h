#include "symbol.h"
#include "utils.h"

typedef int abs_pos;

typedef struct abs_var_ *abs_var;
typedef struct abs_expr_ *abs_expr;
typedef struct abs_dec_ *abs_dec;
typedef struct abs_type_ *abs_type;

typedef struct abs_dec_list_ *abs_dec_list;
typedef struct abs_expr_list_ *abs_expr_list;
typedef struct abs_field_ *abs_field;
typedef struct abs_field_list_ *abs_field_list;
typedef struct abs_fundec_ *abs_fundec;
typedef struct abs_fundec_list_ *abs_fundec_list;
typedef struct abs_namety_ *abs_namety;
typedef struct abs_namety_list_ *abs_namety_list;
typedef struct abs_efield_ *abs_efield;
typedef struct abs_efield_list_ *abs_efield_list;

typedef enum
{  
    ABS_PLUS, ABS_MINUS, ABS_TIMES, ABS_DIVIDE
    ABS_EQ, ABS_NEQ, ABS_LT, ABS_LE, ABS_GT, ABS_GE
} abs_oper;

struct abs_var_
{
    enum { ABS_SIMPLE_VAR, ABS_FIELD_VAR, ABS_SUBSCRIPT_VAR } kind;
    abs_pos pos;
    union 
    {
        s_symbol simple;
        struct { abs_var var; s_symbol sym; } field;
        struct { abs_var var; abs_expr expr; } subscript;
    } u;
};

struct abs_expr_
{
    enum 
    {
        ABS_VAR_EXPR, ABS_NIL_EXPR, ABS_INT_EXPR, ABS_STRING_EXPR,
        ABS_CALL_EXPR, ABS_OP_EXPR, ABS_RECORD_EXPR, ABS_SEQ_EXPR,
        ABS_ASSIGN_EXPR, ABS_IF_EXPR, ABS_WHILE_EXPR, ABS_FOR_EXPR,
        ABS_BREAK_EXPR, ABS_LET_EXPR, ABS_ARRAY_EXPR
    } kind;
    abs_pos pos;
    union
    {
        abs_var var;
        /* nil; */
        int intt;
        string stringg;
        struct { s_symbol func; abs_expr_list args; } call;
        struct { abs_oper oper; abs_expr left; abs_expr right; } op;
        struct { s_symbol type; abs_efield_list fields; } record;
        abs_expr_list seq;
        struct { abs_var var; abs_expr expr; } assign;
        struct { abs_expr test, then, elsee; } iff;
        struct { abs_expr test, body; } whilee;
        struct { s_symbol var; abs_expr lo, hi, body; bool escape; } forr;
        /* breakk; */
        struct { abs_dec_list decs; abs_expr body; } let;
        struct { s_symbol type; abs_expr size, init; } array;
    } u;
};

struct abs_dec_
{
    enum { ABS_FUNCTION_DEC, ABS_VAR_DEC, ABS_TYPE_DEC } kind;
    abs_pos pos;
    union 
    {
        abs_fundec_list function;
        struct { s_symbol var; s_symbol type; abs_expr init; bool escape; } var;
        abs_namety_list type;
    } u;
};

struct abs_type_
{
    enum { ABS_NAME_TYPE, ABS_RECORD_TYPE, ABS_ARRAY_TYPE } kind;
    abs_pos pos;
    union
    {
        s_symbol name;
        abs_field_list record;
        s_symbol array;
    } u;
};

struct abs_field_ { s_symbol name, type; abs_pos pos; bool escape; };
struct abs_field_list_ { abs_field head; abs_field_list tail; };
struct abs_efield_ { s_symbol name; abs_expr expr; };
struct abs_efild_list_ { abs_efield head; abs_efield_list tail; };
struct abs_expr_list_ { abs_expr head; abs_expr_list tail; };
struct abs_fundec_ { abs_pos pos; s_symbol name; abs_field_list params; s_symbol result; abs_expr body; };
struct abs_fundec_list_ { abs_fundec head; abs_fundec_list tail; };
struct abs_dec_list_ { abs_dec head; abs_dec_list tail; };
struct abs_namety_ { s_symbol name; abs_expr expr; };
struct abs_namety_list_ { abs_namety head; abs_namety_list tail; };

abs_var abs_simple_var(abs_pos pos, s_symbol sym);
abs_var abs_field_var(abs_pos pos, abs_var var, s_symbol sym);
abs_var abs_subscript_var(abs_pos pos, abs_var var, abs_expr expr);
abs_expr abs_var_expr(abs_pos pos, abs_var var);
abs_expr abs_nil_expr(abs_pos pos);
abs_expr abs_int_expr(abs_pos pos, int i);
abs_expr abs_string_expr(abs_pos pos, string str);
abs_expr abs_call_expr(abs_pos pos, s_symbol func, abs_expr_list args);
abs_expr abs_op_expr(abs_pos pos, abs_expr left, abs_expr right);
abs_expr abs_record_expr(abs_pos pos, s_symbol type, abs_efield_list fields);
abs_expr abs_seq_expr(abs_pos pos, abs_expr_list seq);
abs_expr abs_assign_expr(abs_pos pos, abs_var var, abs_expr expr);
abs_expr abs_if_expr(abs_pos pos, abs_expr test, abs_expr then, abs_expr elsee);
abs_expr abs_while_expr(abs_pos pos, abs_expr test, abs_expr body);
abs_expr abs_for_expr(abs_pos pos, s_symbol var, abs_expr lo, abs_expr hi, abs_expr body);
abs_expr abs_break_expr(abs_pos pos);
abs_expr abs_let_expr(abs_pos pos, abs_dec_list decs, abs_expr body);
abs_expr abs_array_expr(abs_pos pos, s_symbol type, abs_expr size, abs_expr init);
abs_dec abs_function_dec(abs_pos pos, abs_fundec_list function);
abs_dec abs_var_dec(abs_pos pos, s_symbol var, s_symbol type, abs_expr init);
abs_dec abs_type_dec(abs_pos pos, abs_namety_list type);
abs_type abs_name_type(abs_pos pos, s_symbol name);
abs_type abs_record_type(abs_pos pos, abs_field_list record);
abs_type abs_array_type(abs_pos pos, s_symbol array);
abs_field abs_Field(abs_pos pos, s_symbol name, s_symbol type);
abs_field_list abs_Field_list(abs_field head, abs_field_list tail);
abs_expr_list abs_Expr_list(abs_expr head, abs_expr_list tail);
abs_fundec abs_Fundec(abs_pos pos, s_symbol name, abs_field_list params, s_symbol result, abs_expr body);
abs_fundec_list abs_Fundec_list(abs_fundec head, abs_fundec_list tail);
abs_dec_list abs_Dec_list(abs_dec head, abs_dec_list tail);
abs_namety abs_Namety(s_symbol name, abs_type type);
abs_namety_list abs_Namety_list(abs_namety head, abs_namety_list tail);
abs_efield abs_Efield(s_symbol name, abs_expr expr);
abs_efield_list abs_efield_list(abs_efield head, abs_efield_list tail);