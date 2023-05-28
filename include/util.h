#ifndef UTIL_H
#define UTIL_H

#include <string.h>

#define TRUE 1
#define FALSE 0

void bool_to_str(int value_int, char *value_str);

// definición del tipo de puntero a función
typedef void (*pointer_func_t)(const void *);

// función genérica para imprimir una estructura utilizando el puntero a función
void imprimir_estructura(const void *estructura, pointer_func_t imprimir);

// definición del tipo de puntero a función
typedef void (*pointer_func_asignar_t)(const void *, const void *);

#endif