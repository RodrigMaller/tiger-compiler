#define TABSIZE 127

typedef struct TAB_table_ *TAB_table;

TAB_table TAB_empty(void);

void TAB_enter(TAB_table t, void *key, void *value);

void *TAB_lookup(TAB_table t, void *key);

void *TAB_pop(TAB_table t);

void TAB_dump(TAB_table t, void (*show)(void *key, void *value));
