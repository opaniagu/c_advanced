#include "todo.h"

void todo_print(todo_t *task)
{
    char complete_bool_str[6];

    bool_to_str(task->complete, complete_bool_str);
    fprintf(stderr, "(%d|%s|%s)\n", task->id, task->title, complete_bool_str);
    // fprintf(stderr, "(%d|%s|%d)\n", task->id, task->title, task->complete);
}

void todo_print_ptr(const void *tarea)
{
    // char complete_bool_str[6];

    // casting
    todo_t *task = (todo_t *)tarea;

    todo_print(task);

    // bool_to_str(task->complete, complete_bool_str);
    // fprintf(stderr, "(%d|%s|%s)\n", task->id, task->title, complete_bool_str);
}