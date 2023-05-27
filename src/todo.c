#include "todo.h"

void todo_print(todo_t *task)
{
    fprintf(stderr, "(%d|%s|%d)\n", task->id, task->title, task->complete);
}