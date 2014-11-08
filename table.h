#define TABSIZE 127

typedef struct tab_table_ *tab_table;

tab_table tab_empty(void);

void tab_enter(tab_table t, void *key, void *value);

void *tab_lookup(tab_table t, void *key);

void *tab_pop(tab_table t);

void tab_dump(tab_table t, void (*show)(void *key, void *value));
