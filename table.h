#define TABSIZE 127

typedef struct table_ *table;

table tab_empty(void);

void tab_enter(table t, void *key, void *value);

void *tab_look(table t, void *key);

void *tab_pop(table t);

void tab_dump(table t, void (*show)(void *key, void *value));
