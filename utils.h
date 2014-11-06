#include <assert.h>

typedef char *string;

typedef char bool;
#define TRUE 1
#define FALSE 0

typedef struct list_ *list;
struct list
{
    union
    {
        int i;
        bool b;
    };
    list tail;
};

void *checked_malloc(int);

string String(char *);

list bool_list(bool head, list tail);

list int_list(int head, list tail);
