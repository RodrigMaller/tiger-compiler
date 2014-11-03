/* scanner for a toy Pascal-like language */
     
%{
/* need this for the call to atof() below */
#include <string.h>

#include "utils.h"
#include "tokens.h"
#include "errormsg.h"

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
     
%%
     
" "     { adj(); continue; }
\n      { adj(); EM_newline(); continue; }
","     { adj(); return COMMA; }
for     { adj(); return FOR; }
[0-9]+  { adj(); yylval.ival = atoi(yytext); return INT; }
.       { adj(); EM_error(EM_tok_pos, "illegal token"); }
