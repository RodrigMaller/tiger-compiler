#include "utils.h"
#include "table.h"

#define SIZE 109

typedef struct s_symbol_ *s_symbol;

s_symbol S_Symbol(string);

string s_name(s_symbol);

typedef struct tab_table_ *s_table;

s_table s_empty(void);

void s_enter(s_table tab, s_symbol sym, void *value);

void *s_lookup(s_table tab, s_symbol sym);

void s_begin_scope(s_table tab);

void s_end_scope(s_table tab);