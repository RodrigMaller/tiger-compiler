#include <assert.h>

typedef char *string;

typedef char bool;
#define TRUE 1
#define FALSE 0

typedef struct L_list_ *L_list;
struct L_list_
{
    union
    {
        int i;
        bool b;
        void *data;
    };
    struct L_list_ *tail;
};

void *checked_malloc(int);

string String(char *);

L_list bool_list(bool head, L_list tail);

L_list int_list(int head, L_list tail);

L_list list(void *data, L_list tail);
