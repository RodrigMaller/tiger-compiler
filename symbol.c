#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "symbol.h"

struct S_symbol_
{
    string name;
    S_symbol next;
}

static S_symbol mk_symbol(string name, S_symbol next)
{
    S_symbol sym = checked_malloc(sizeof(*s));
    sym->name = name;
    sym->next = next;
    return sym;
}

static S_symbol hashtable[SIZE];

static unsigned int hash(string str)
{
    unsigned int h = 0;
    char *s;
    
    for(s = str; *s; s++)
        h = 65599 * h + *s;
    return h;
}

S_symbol S_Symbol(string name)
{
    int index = hash(name) % SIZE;
    S_symbol syms = hashtable[index], sym;
    
    for(sym = syms; sym; sym = sym->next)
        if(strcmp((string) sym->name, name))
            return sym;
    sym = mk_symbol(name, syms);
    hashtable[index] = sym;
    return sym;
}

string S_name(S_symbol sym)
{
    return (string) sym->name;
}

S_table S_empty(void)
{
    return TAB_empty();
}

void S_enter(S_table tab, S_symbol sym, void *value)
{
    TAB_enter(tab, sym, value);
}

void *S_lookup(S_table tab, S_symbol sym)
{
    return TAB_lookup(tab, sym);
}

static struct S_symbol_ _mark_sym = {"<mark>", 0};

void S_begin_scope(S_table tab)
{
    S_enter(tab, &_mark_sym, NULL);
}

void S_end_scope(S_table tab)
{
    S_symbol sym;
    
    do
        sym = TAB_pop(tab);
    while (sym != _mark_sym);
}

void S_dump(S_table tab, void (*show)(S_symbol sym, void *binding))
{
    TAB_dump(tab, (void (*)(void *, void *)) show);
}