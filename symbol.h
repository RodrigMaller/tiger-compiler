#include "utils.h"
#include "table.h"

#define SIZE 109

typedef struct S_symbol_ *S_symbol;

S_symbol S_Symbol(string);

string S_name(S_symbol);

typedef struct TAB_table_ *S_table;

S_table S_empty(void);

void S_enter(S_table tab, S_symbol sym, void *value);

void *S_lookup(S_table tab, S_symbol sym);

void S_begin_scope(S_table tab);

void S_end_scope(S_table tab);
