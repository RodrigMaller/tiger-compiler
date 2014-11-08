#include <stdio.h>
#include <assert.h>

#include "util.h"
#include "tab_table.h"

typedef struct binder_ *binder;
struct binder_
{
    void *key;
    void *value;
    binder next;
    void *prevtop;
};

struct tab_table_
{
    binder tab_table[TABSIZE];
    void *top;
};

static binder Binder(void *key, void *value, binder next, void *prevtop)
{
    binder b = checked_malloc(sizeof(*b));
    b->key = key;
    b->value = value;
    b->next = next;
    b-> prevtop = prevtop;
    return b;
}

tab_table tab_empty(void)
{
    table t = checked_malloc(sizeof(*t));
    int i;
    
    t->top = NULL;
    for (i = 0; i < TABSIZE; i++)
        t->table[i] = NULL;
    return t;
}

void tab_enter(tab_table t, void *key, void value)
{
    int index;
    
    assert(t && key);
    index = ((unsigned) key) % TABSIZE;
    t->tab_table[index] = Binder(key, value, t->tab_table[index], t->top);
    t->top = key;
}

void *tab_lookup(tab_table t, void *key)
{
    int index;
    
    binder b;
    assert(t && key);
    index = ((unsigned) key) % TABSIZE;
    for(b = t->tab_table[index]; b; b = b->next)
        if (b->key == key) return b->value;
    return NULL;
}

void *tab_pop(tab_table t)
{
    void *k;
    binder b;
    int index;
    
    assert(t);
    k = t->top;
    assert(k);
    index = ((unsigned) k) % TABSIZE;
    b = t->tab_table[index];
    assert(b);
    t->tab_table[index] = b->next;
    t->top = b->prevtop;
    return b->key;
}

void tab_dump(tab_table t, void (*show)(void *key, void *value))
{
    void *k = t->top;
    int index = ((unsigned) k) % TABSIZE;
    binder b = t->tab_table[index];
    if (b == NULL) return;
    t->tab_table[index] = b->next;
    t->top = b->prevtop;
    show(b->key, b->value);
    tab_dump(t, show);
    assert(t->top == b->prevtop && t->tab_table[index] == b->next);
    t->top = k;
    t->tab_table[index] = b;
}
