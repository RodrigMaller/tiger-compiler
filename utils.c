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

L_list bool_list(bool b, L_list tail)
{
    L_list l = checked_malloc(sizeof(*l));
    l->b = b;
    l->tail = tail;
    return l;
}

L_list int_list(int i, L_list tail)
{
    L_list l = checked_malloc(sizeof *l);
    l->i = i;
    l->tail = tail;
    return l;
}

L_list list(void *data, L_list tail)
{
    L_list p = checked_malloc(sizeof(*p));
    p->data = data;
    p->tail = tail;
    return p;
}
