#ifndef TODO_H
#define TODO_H

#include <stdio.h>
#include "util.h"

#define TITLE_LEN 128

typedef struct todo
{
    int id;
    char title[TITLE_LEN];
    int complete;
} todo_t;

// funcion que imprime la estructura
void todo_print(todo_t *task);

// funcion que imprime la estructura, pero la voy a utilizar
// con punteros a funciones
void todo_print_ptr(const void *);

#endif