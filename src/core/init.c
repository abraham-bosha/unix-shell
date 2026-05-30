#include <stdlib.h>

#include "shell.h"

int shell_init(void)
{
    shell = calloc(1, sizeof(*shell));

    if (!shell)
        return (-1);

    shell->last_status = 0;

    return (0);
}
