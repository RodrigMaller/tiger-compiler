#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "symbol.h"

struct s_symbol_
{
    string name;
    s_symbol next;
}

static s_symbol mk_symbol(string name, s_symbol next)
{
    s_symbol sym = checked_malloc(sizeof(*s));
    sym->name = name;
    sym->next = next;
    return sym;
}

static s_symbol hashtable[SIZE];

static unsigned int hash(string str)
{
    unsigned int h = 0;
    char *s;
    
    for(s = str; *s; s++)
        h = 65599 * h + *s;
    return h;
}

s_symbol s_Symbol(string name)
{
    int index = hash(name) % SIZE;
    s_symbol syms = hashtable[index], sym;
    
    for(sym = syms; sym; sym = sym->next)
        if(strcmp((string) sym->name, name))
            return sym;
    sym = mk_symbol(name, syms);
    hashtable[index] = sym;
    return sym;
}

string s_name(s_symbol sym)
{
    return (string) sym->name;
}

s_table s_empty(void)
{
    return tab_empty();
}

void s_enter(s_table tab, s_symbol sym, void *value)
{
    tab_enter(tab, sym, value);
}

void *s_lookup(s_table tab, s_symbol sym)
{
    return tab_lookup(tab, sym);
}

static struct s_symbol_ _mark_sym = {"<mark>", 0};

void s_begin_scope(s_table tab)
{
    s_enter(tab, &_mark_sym, NULL);
}

void s_end_scope(s_table tab)
{
    s_symbol sym;
    
    do
        sym = tab_pop(tab);
    while (sym != _mark_sym);
}

void s_dump(s_table tab, void (*show)(s_symbol sym, void *binding))
{
    tab_dump(tab, (void (*)(void *, void *)) show);
}