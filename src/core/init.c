#include <string.h>

#include "shell.h"

int shell_init(shell_t *shell)
{
    memset(shell, 0, sizeof(*shell));

    shell->running = true;

    return (0);
}
