#include "data.h"

void data_print(data_t *data)
{
    char complete_bool_str[6];

    bool_to_str(data->complete, complete_bool_str);
    fprintf(stderr, "(%d|%s|%s)\n", data->id, data->title, complete_bool_str);
}

void data_print_ptr(const void *ptr)
{
    data_t *data = (data_t *)ptr;
    data_print(data);
}

void asign_data(const void *p1, const void *p2)
{
    data_t *r1 = (data_t *)p1;
    data_t *r2 = (data_t *)p2;

    *r1 = *r2;
}