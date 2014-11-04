%{
#include <stdio.h>
#include "utils.h"
#include "errormsg.h"

int yylex(void);

void yyerror(char *s)
{
    EM_error(EM_tok_pos, "%s", s);
}
%}

%union 
{
    int pos;
    int ival;
    string sval;
}

%token <sval> ID STRING
%token <ival> INT

%token 
    TK_COMMA TK_COLON TK_SEMICOLON TK_LPAREN TK_RPAREN TK_LBRACK TK_RBRACK
    TK_LBRACE TK_RBRACE TK_DOT
    TK_PLUS TK_MINUS TK_TIMES TK_DIVIDE TK_EQ TK_NEQ TK_LT TK_LE TK_GT TK_GE
    TK_AND TK_OR TK_ASSIGN
    TK_ARRAY TK_IF TK_THEN TK_ELSE TK_WHILE TK_FOR TK_TO TK_DO TK_LET TK_IN TK_END TK_OF
    TK_BREAK TK_NIL
    TK_FUNCTION TK_VAR TK_TYPE

%start program

%%

program: 
  exp

exp: 
  exp
| 
















