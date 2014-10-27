#ifndef UTILS_H
#define UTILS_H

#include <assert.g>

typedef char *string;
string String(char *);

typedef char bool;
#define TRUE 1
#define FALSE 0

void *checked_malloc(int);
