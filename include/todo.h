#ifndef TODO_H
#define TODO_H

#define TRUE 1
#define FALSE 0

#define TITLE_LEN 128

typedef struct todo
{
    int id;
    char title[TITLE_LEN];
    int complete;
} todo_t;

#endif