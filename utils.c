#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"

void *checked_malloc(int len)
{
    void *p = malloc(len);
    assert(p);
    return p;
}

string String(char *str)
{
    string p = checked_malloc(strlen(str) + 1);
    strcpy(p, str);
    return p;
}

list bool_list(bool b, list tail)
{
    list l = checked_malloc(sizeof(*l));
    l->b = b;
    l->tail = tail;
    return l;
}

list int_list(int i, list tail)
{
    list l = checked_malloc(sizeof *l);
    l->i = i;
    l->tail = tail;
    return l;
}
