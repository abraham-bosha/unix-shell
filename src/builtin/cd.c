#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#include "command.h"
#include "shell.h"

int builtin_cd(shell_t *shell, command_t *cmd)
{
    if (cmd->argc > 2)
    {
        fprintf(stderr, "unix-shell: cd: too many arguments\n");
        return (1);
    }

    char *dest = (cmd->argc == 2) ? cmd->argv[1] : NULL;
    char *expanded_path = NULL;

    if (dest == NULL || strcmp(dest, "~") == 0)
    {
        dest = getenv("HOME");
        if (dest == NULL)
        {
            fprintf(stderr, "unix-shell: cd: HOME not set\n");
            return (1);
        }
    }
    else if (strcmp(dest, "-") == 0)
    {
        dest = shell->oldpwd;
        if (dest == NULL)
        {
            fprintf(stderr, "unix-shell: cd: OLDPWD not set\n");
            return (1);
        }
        
        printf("%s\n", dest);
    }
    else if (dest[0] == '~' && dest[1] == '/')
    {
        char *home_dir = getenv("HOME");
        if (home_dir == NULL)
        {
            fprintf(stderr, "unix-shell: cd: HOME not set\n");
            return (1);
        }

        size_t needed_space = strlen(home_dir) + strlen(dest + 1) + 1;
        expanded_path = malloc(needed_space);

        if (expanded_path == NULL)
        {
            perror("cd: malloc failed");
            return (1);
        }

        strcpy(expanded_path, home_dir);
        strcat(expanded_path, dest + 1);

        dest = expanded_path;
    }

    char *current_dir = getcwd(NULL, 0);
    if (current_dir == NULL)
    {
        perror("cd: getcwd failed");
        free(expanded_path);
        return (1);
    }

    if (chdir(dest) != 0)
    {
        perror("cd");
        free(current_dir);
        free(expanded_path);
        return (1);
    }

    free(expanded_path);

    if (shell->oldpwd != NULL)
    {
        free(shell->oldpwd);
    }

    shell->oldpwd = current_dir;

    setenv("OLDPWD", shell->oldpwd, 1);

    char *new_cwd = getcwd(NULL, 0);
    if (new_cwd != NULL)
    {
        setenv("PWD", new_cwd, 1);
        free(new_cwd);
    }

    return (0);
}
