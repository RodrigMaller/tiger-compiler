/* scanner for a toy Pascal-like language */
     
%{
/* need this for the call to atof() below */
#include <string.h>

#include "errormsg.h"
#include "parser.tab.h"

int char_pos = 1;

int yywrap(void)
{
    char_pos = 1;
    return 1;
}

void adj(void)
{
    EM_tok_pos = char_pos;
    char_pos+=yyleng;
}

%}

DIGIT   [0-9]
ID      [a-zA-Z][a-zA-Z0-9]*
     
%%

[ \t\f\v\r]             { adj(); }
\n                      { adj(); EM_newline(); }
     
","             { adj(); return TK_COMMA; }
":"             { adj(); return TK_COLON;}
";"             { adj(); return TK_SEMICOLON; }
"("             { adj(); return TK_LPAREN; }
")"             { adj(); return TK_RPAREN; }
"["             { adj(); return TK_LBRACK; }
"]"             { adj(); return TK_RBRACK; }
"{"             { adj(); return TK_LBRACE; }
"}"             { adj(); return TK_RBRACE; }
"."             { adj(); return TK_DOT; }
"+"             { adj(); return TK_PLUS; }
"-"             { adj(); return TK_MINUS; }
"*"             { adj(); return TK_TIMES; }
"/"             { adj(); return TK_DIVIDE; }
"="             { adj(); return TK_EQ; }
"<>"            { adj(); return TK_NEQ; }
"<"             { adj(); return TK_LT; }
"<="            { adj(); return TK_LE; }
">"             { adj(); return TK_GT; }
">="            { adj(); return TK_GE; }
"&"             { adj(); return TK_AND; }
"|"             { adj(); return TK_OR; }
":="            { adj(); return TK_ASSIGN; }

array           { adj(); return TK_ARRAY; }
if              { adj(); return TK_IF; }
then            { adj(); return TK_THEN; }
else            { adj(); return TK_ELSE; }
while           { adj(); return TK_WHILE; }
for             { adj(); return TK_FOR; }
to              { adj(); return TK_TO; }
do              { adj(); return TK_DO; }
let             { adj(); return TK_LET; }
in              { adj(); return TK_IN; }
end             { adj(); return TK_END; }
of              { adj(); return TK_OF; }
break           { adj(); return TK_BREAK; }
nil             { adj(); return TK_NIL; }
function        { adj(); return TK_FUNCTION; }
var             { adj(); return TK_VAR; }
type            { adj(); return TK_TYPE; }

{DIGIT}+        { adj(); yylval.ival = atoi(yytext); return TK_INT; }
{ID}            { adj(); yylval.sval = String(yytext); return TK_ID; }
