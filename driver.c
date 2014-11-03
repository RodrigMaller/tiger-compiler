#include <stdio.h>
#include <stdlib.h>

#include "utils.h"
#include "errormsg.h"
#include "tokens.h"

YYSTYPE yylval;
 
int yylex(void);

string token_names[] =
{
    "ID", "STRING", "INT", "COMMA", "COLON", "SEMICOLON", "LPAREN",
    "RPAREN", "LBRACK", "RBRACK", "LBRACE", "RBRACE", "DOT", "PLUS",
    "MINUS", "TIMES", "DIVIDE", "EQ", "NEQ", "LT", "LE", "GT", "GE",
    "AND", "OR", "ASSIGN", "ARRAY", "IF", "THEN", "ELSE", "WHILE", "FOR",
    "TO", "DO", "LET", "IN", "END", "OF", "BREAK", "NIL", "FUNCTION",
    "VAR", "TYPE"
};

string token_name(token)
{
    return token<257 || token>299 ? "BAD_TOKEN" : token_names[token-257];
}

int main(int argc, char **argv)
{
    string fname;
    int token;
    
    if (argc != 2)
    {
        fprintf(stderr, "usage: a.out filename\n");
        exit(1);
    }
    
    fname = argv[1];
    EM_reset(fname);
    for(;;)
    {
        token = yylex();
        if (token == 0) break;
        switch(token)
        {
            case ID: case STRING:
                printf("%10s %4d %s\n", token_name(token), EM_tok_pos, yylval.sval);
                break;
            case INT:
                printf("%10s %4d %d\n", token_name(token), EM_tok_pos, yylval.ival);
                break;
            default:
                printf("%10s %4d\n", token_name(token), EM_tok_pos);
        }
    }
    return 0;
}
