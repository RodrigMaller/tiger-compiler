%{
#include <stdio.h>
#include <stdlib.h>

#include "errormsg.h"

int yylex(void);

void yyerror(char *s);
%}

%union 
{
    int pos;
    int ival;
    string sval;
    L_list list;
    S_symbol sym;
    ABS_var var;
    ABS_expr expr;
    ABS_dec dec;
    ABS_fundec func;
    ABS_type type;
}

%{

static void print_tk_value(FILE *fp, int type, YYSTYPE value);
#define YYPRINT(fp, type, value) print_tk_value(fp, type, value)

#define LIST_ACTION(target, prev, elem) \
    do \
    { \
        L_list p, e = list((elem), NULL); \
        (target) = p = (prev); \
        if (p) \
        { \
            while (p->tail) \
                p = p->tail; \
            p->tail = e; \
        } \
        else \
            (target) = e; \
    } \
    while(FALSE);

#define LVALUE_ACTION(target, prev, elem) \
    do \
    { \
        ABS_var p, var = (elem); \
        (target) = p = (prev); \
        if (p) \
        { \
            while(p->u.field.var) \
                p = p->u.field.var; \
            p->u.field.var = var; \
        } \
        else \
            (target) = var; \
    } \
    while(FALSE);

static ABS_expr absyn_root;

%}

%token <sval> TK_ID TK_STRING
%token <ival> TK_INT

%token <pos> 
    TK_COMMA TK_COLON TK_LPAREN TK_RPAREN TK_LBRACK TK_RBRACK
    TK_LBRACE TK_RBRACE TK_DOT
    TK_ARRAY TK_IF TK_THEN TK_ELSE TK_WHILE TK_FOR TK_TO TK_LET TK_IN TK_END TK_OF
    TK_BREAK TK_NIL
    TK_FUNCTION TK_VAR TK_TYPE
    
%left <pos> TK_SEMICOLON
%nonassoc <pos> TK_DO
%nonassoc <pos> TK_ASSIGN
%left <pos> TK_OR
%left <pos> TK_AND
%nonassoc <pos> TK_EQ TK_NEQ TK_LT TK_LE TK_GT TK_GE
%left <pos> TK_PLUS TK_MINUS
%left <pos> TK_TIMES TK_DIVIDE
%left <pos> TK_UMINUS

%type <dec> dec var_dec
%type <expr> program expr
%type <type> type
%type <var> lval lval_
%type <list> expr_seq arg_seq efield_seq decs funcs_dec types_dec fields
%type <list> field_seq
%type <func> func_dec
%type <sym> id

%start program

%%

/* input:
 {   }
| input line
;

line:
  '\n'
| expr '\n'   { printf ("##\t%.10g\n", $1); }
| error '\n'  { yyerrok;                  }
;
*/

program:
  expr      { absyn_root = $1; }
;

expr: 
//  TK_NIL                                            { $$ = ABS_nil_expr($1); }
//| TK_BREAK                                          { $$ = ABS_break_expr($1); }
  TK_INT                                            { $$ = ABS_int_expr(EM_tok_pos, $1); }
//| TK_STRING                                         { $$ = ABS_string_expr(EM_tok_pos, $1); }
| lval                                              { $$ = ABS_var_expr($1->pos, $1); }
| TK_LPAREN TK_RPAREN                               { $$ = ABS_seq_expr($1, NULL); }
| TK_LPAREN expr TK_RPAREN                          { $$ = $2; }
| id TK_LPAREN TK_RPAREN                            { $$ = ABS_call_expr($2, $1, NULL); }
| id TK_LPAREN expr arg_seq TK_RPAREN               { $$ = ABS_call_expr($2, $1, list($3, $4)); }
//| TK_MINUS expr %prec TK_UMINUS                     { $$ = ABS_op_expr($1, ABS_int_expr($1, 0), ABS_MINUS, $2); }
| expr TK_PLUS expr                                 { $$ = ABS_op_expr($2, ABS_PLUS, $1, $3); }
| expr TK_MINUS expr                                { $$ = ABS_op_expr($2, ABS_MINUS, $1, $3); }
| expr TK_TIMES expr                                { $$ = ABS_op_expr($2, ABS_TIMES, $1, $3); }
| expr TK_DIVIDE expr                               { $$ = ABS_op_expr($2, ABS_DIVIDE, $1, $3); }
//| expr TK_EQ expr                                   { $$ = ABS_op_expr($2, $1, ABS_EQ, $3); }
//| expr TK_NEQ expr                                  { $$ = ABS_op_expr($2, $1, ABS_NEQ, $3); }
//| expr TK_LT expr                                   { $$ = ABS_op_expr($2, $1, ABS_LT, $3); }
//| expr TK_LE expr                                   { $$ = ABS_op_expr($2, $1, ABS_LE, $3); }
//| expr TK_GT expr                                   { $$ = ABS_op_expr($2, $1, ABS_GT, $3); }
//| expr TK_GE expr                                   { $$ = ABS_op_expr($2, $1, ABS_GE, $3); }
//| expr TK_AND expr                                  { $$ = ABS_if_expr($2, $1, $3, ABS_int_expr($2, 0)); }
//| expr TK_OR expr                                   { $$ = ABS_if_expr($2, $1, ABS_int_expr($2, 1), $3); }
//| lval TK_ASSIGN expr                               { $$ = ABS_assign_expr($2, $1, $3); }
//| id TK_LBRACE TK_RBRACE                            { $$ = ABS_record_expr($2, $1, NULL); }
//| id TK_LBRACE id TK_EQ expr efield_seq TK_RBRACE   { $$ = ABS_record_expr($2, $1, list(ABS_Efield($4, $3, $5), $6)); }
//| id TK_LBRACK expr TK_RBRACK TK_OF expr            { $$ = ABS_array_expr($2, $1, $3, $6); }
//| TK_IF expr TK_THEN expr                           { $$ = ABS_if_expr($1, $2, $4, NULL); }
//| TK_IF expr TK_THEN expr TK_ELSE expr              { $$ = ABS_if_expr($1, $2, $4, $6); }
//| TK_WHILE expr TK_DO expr                          { $$ = ABS_while_expr($1, $2, $4); }
//| TK_FOR id TK_ASSIGN expr TK_TO expr TK_DO expr    { $$ = ABS_for_expr($1, $2, $4, $6, $8); }
| TK_LET decs TK_IN expr TK_END                     { $$ = ABS_let_expr($1, $2, $4); }
;

decs:
  /* empty */           { $$ = NULL; }
| decs dec              { LIST_ACTION($$, $1, $2); }
;

dec:
  types_dec             { $$ = ABS_type_dec(((ABS_type) $1->data)->pos, $1); }
| var_dec
| funcs_dec             { $$ = ABS_function_dec(((ABS_fundec) $1->data)->pos, $1); }
;

types_dec:
  TK_TYPE id TK_EQ type             { $$ = list(ABS_Namety($2, $4), NULL); }
| types_dec TK_TYPE id TK_EQ type   { LIST_ACTION($$, $1, ABS_Namety($3, $5)); }
;

type:
  id                                { $$ = ABS_name_type(EM_tok_pos, $1); }
| TK_LBRACE fields TK_RBRACE        { $$ = ABS_record_type($1, $2); }
| TK_ARRAY TK_OF id                 { $$ = ABS_array_type($1, $3); }
;

fields:
  /* empty */                       { $$ = NULL; }
| id TK_COLON id field_seq          { $$ = list(ABS_Field($1, $3), $4); }
;

var_dec:
  TK_VAR id TK_ASSIGN expr              { $$ = ABS_var_dec($1, $2, NULL, $4); }
//| TK_VAR id TK_COLON id TK_ASSIGN expr  { $$ = ABS_var_dec($1, $2, $4, $6); }
;

funcs_dec:
  func_dec              { $$ = list($1, NULL); }
| funcs_dec func_dec    { LIST_ACTION($$, $1, $2); }
;

func_dec:
  TK_FUNCTION id TK_LPAREN fields TK_RPAREN TK_EQ expr              { $$ = ABS_Fundec($1, $2, $4, NULL, $7); }
| TK_FUNCTION id TK_LPAREN fields TK_RPAREN TK_COLON id TK_EQ expr  { $$ = ABS_Fundec($1, $2, $4, $7, $9); }
;

//expr_seq:
//  TK_SEMICOLON expr             { $$ = list($2, NULL); }
//| expr_seq TK_SEMICOLON expr    { $$ = LIST_ACTION($$, $1, $2); }
//
arg_seq:
  /* empty */                   { $$ = NULL; }
| arg_seq TK_COMMA expr         { LIST_ACTION($$, $1, $3); }
;

//efield_seq:
//  /* empty */                           { $$ = NULL; }
//| efield_seq TK_COMMA id TK_EQ expr     { LIST_ACTION($$, $1, ABS_Efield($4, $3, $5)); }
//
field_seq:
  /* empty */                           { $$ = NULL; }
| field_seq TK_COMMA id TK_COLON id     { LIST_ACTION($$, $1, ABS_Field($3, $5)); }
;

lval:
  id lval_        { LVALUE_ACTION($$, $2, ABS_simple_var(EM_tok_pos, $1)); }
;

lval_:
  /* empty */                           { $$ = NULL; }
| TK_DOT id lval_                       { LVALUE_ACTION($$, $3, ABS_field_var($1, NULL, $2)); }
| TK_LBRACK expr TK_RBRACK lval_        { LVALUE_ACTION($$, $4, ABS_subscript_var($1, NULL, $2)); }
;

id:
  TK_ID     { $$ = S_Symbol($1); }
;
  
%%

void yyerror(char *s)
{
    EM_error(EM_tok_pos, "%s", s);
}

static void print_tk_value(FILE *fp, int type, YYSTYPE value)
{
    switch (type)
    {
        case TK_ID:
        case TK_STRING:
            fprintf(fp, "%s", value.sval);
            break;
        case TK_INT:
            fprintf(fp, "%d", value.ival);
            break;
    }
}

ABS_expr parse(string filename)
{
    EM_reset(filename);
    if(yyparse() == 0)
        return absyn_root;
    else
        return NULL;
}
