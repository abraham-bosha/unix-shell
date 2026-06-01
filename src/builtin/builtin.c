#include <string.h>

#include "command.h"

extern int build_pwd(command_t *cmd);

int is_builtin(command_t *cmd)
{
    if (!cmd)
        return 0;

    if (cmd->argc == 0)
        return 0;

    return (strcmp(cmd->argv[0], "pwd") == 0);
}

int execute_builtin(command_t *cmd)
{

    if (strcmp(cmd->argv[0], "pwd") == 0)
    {
        return build_pwd(cmd);
    }

    return (1);

}



