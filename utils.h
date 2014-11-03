#ifndef UTILS_H
#define UTILS_H

#include <assert.h>

typedef char *string;

typedef char bool;
#define TRUE 1
#define FALSE 0

typedef struct bool_list *bool_list;
struct bool_list
{
    bool head;
    bool_list tail;
};

void *checked_malloc(int);
string String(char *);
bool_list bool_list(bool head, bool_list tail);
