#include <stdio.h>

#include "absyn.h"

void pr_expr(FILE *fp, ABS_expr v, int d);
void pr_var(FILE *fp, ABS_var v, int d);
void pr_dec(FILE *fp, ABS_dec v, int d);
void pr_type(FILE *fp, ABS_type v, int d);