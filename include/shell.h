#ifndef SHELL_H
#define SHELL_H

#include <stdbool.h>

#include "variable.h"

typedef struct shell
{
    bool running;

    int exit_status;

    int last_exit_status;

    char *oldpwd;

    variable_t *vars;

    int varc;

} shell_t;

int shell_init(shell_t *shell);
void shell_loop(shell_t *shell);

#endif
