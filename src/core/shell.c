#include <stdio.h>

#include "shell.h"
#include "variable.h"

int main(void) 
{
    shell_t shell;

    if (shell_init(&shell) < 0)
        return 1; 

    shell_init(&shell);
    
    shell_loop(&shell);

    shell_destroy(&shell);

    return shell.exit_status;
}


