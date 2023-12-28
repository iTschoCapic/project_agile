#include <stdbool.h>
#include <stdlib.h>

void check_if_error(bool expr, char *msg)
{
    if (expr)
    {
        fprintf(stderr, "%s\n", msg);
        exit(EXIT_FAILURE);
    }
}