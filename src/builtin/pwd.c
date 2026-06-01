#include <stdio.h>
#include <unistd.h>
#include <limits.h>

#include "command.h"

int build_pwd(command_t *cmd)
{
    (void)cmd;

    char cwd[PATH_MAX];

    if(!getcwd(cwd, sizeof(cwd)))
        return (1);

    printf("%s\n", cwd);

    return (0);
}


