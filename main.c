#include <stdio.h>
#include <stdlib.h>

#include "prabsyn.h"

int main(int argc, char **argv)
{
    ABS_expr prog;
    
    if(!(prog = parse(argv[1])))
        exit(1);
    
    pr_expr(stdout, prog, 0);
    
    return 0;
}
