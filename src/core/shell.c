#include <stdio.h>

#include "shell.h"

shell_t *shell;

int main(void) 
{
    shell_init();
    shell_loop();

    return (0);
}


