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

%type <exp> program exp

%start program

%%

program: 
  exp

exp: 
  ID
















