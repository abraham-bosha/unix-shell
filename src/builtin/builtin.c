#include <string.h>

#include "command.h"
#include "builtin.h"
#include "shell.h"

extern int builtin_pwd(command_t *cmd);
extern int builtin_exit(command_t *cmd);
extern int builtin_cd(shell_t *shell, command_t *cmd);

int is_builtin(command_t *cmd)
{
    if (!cmd)
        return 0;

    if (cmd->argc == 0)
        return 0;

    return (
        strcmp(cmd->argv[0], "pwd") == 0 ||
        strcmp(cmd->argv[0], "exit") == 0 ||
        strcmp(cmd->argv[0], "cd") == 0
    );
}

int execute_builtin(shell_t *shell, command_t *cmd)
{

    if (strcmp(cmd->argv[0], "pwd") == 0)

        return builtin_pwd(cmd);

    else if (strcmp(cmd->argv[0], "exit") == 0)

        return builtin_exit(cmd);

    else if (strcmp(cmd->argv[0], "cd") == 0)

        return builtin_cd(shell, cmd);

    return (1);

}



