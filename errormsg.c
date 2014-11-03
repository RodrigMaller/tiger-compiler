#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#include "utils.h"
#include "errormsg.h"

bool any_errors = FALSE;

static string file_name = "";

static int line_num = 1;

int EM_tok_pos = 0;

extern FILE *yyin;

static list line_pos = NULL;

void EM_newline(void)
{
    line_num++;
    line_pos = int_list(EM_tok_pos, line_pos);
}

void EM_error(int pos, char *msg,...)
{
    va_list ap;
    list lines = line_pos;
    int num = line_num;
    
    any_errors = TRUE;
    while (lines && lines->i >= pos)
    {
        lines = lines->tail;
        num--;
    }
    
    if (file_name) fprintf(stderr, "%s:", file_name);
    if (lines) fprintf(stderr, "%d.%d: ", num, pos - lines->i);
    va_start(ap, msg);
    vfprintf(stderr, msg, ap);
    va_end(ap);
    fprintf(stderr, "\n");
}

void EM_reset(string fname)
{
    any_errors = FALSE;
    file_name = fname;
    line_num = 1;
    
    line_pos = int_list(0, NULL);
    yyin = fopen(fname, "r");
    if (!yyin)
    {
        EM_error(0, "cannot open");
        exit(1);
    }
}
