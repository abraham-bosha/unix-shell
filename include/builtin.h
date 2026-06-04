#ifndef BUILTIN_H
#define BUILTIN_H

#include "command.h"
#include "shell.h"

int is_builtin(command_t *cmd);

int execute_builtin(shell_t *shell, command_t *cmd);

#endif
