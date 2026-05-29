#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <readline/readline.h>
#include <readline/history.h>

#include "shell.h"
#include "prompt.h"

void shell_loop(void)
{
    char *line;
    
    while (true)
    {
        line = readline(prompt_build());

        if (line == NULL)
        {
            printf("exit\n");
            break;
        }

        if (*line != '\0')
            add_history(line);

        free(line);
    }
}
