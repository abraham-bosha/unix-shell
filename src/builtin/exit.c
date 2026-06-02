#include <stdlib.h>

#include "command.h"

int builtin_exit(command_t *cmd)
{
    (void)cmd;
    
    exit(0);
}
