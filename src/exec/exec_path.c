#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>

#include "exec_path.h"

static int is_executable(const char *path)
{
    return access(path, X_OK) == 0;
}

char *resolve_path(const char *cmd)
{
    char *path_env;
    char *paths;
    char *token;
    char *full_path;
    size_t len;

    if (!cmd || strchr(cmd, '/'))
        return (is_executable(cmd) ? strdup(cmd) : NULL);

    path_env = getenv("PATH");
    if (!path_env)
        return NULL;

    paths = strdup(path_env);
    if (!paths)
        return NULL;

    token = strtok(paths, ":");
    while (token)
    {
        len = strlen(token) + strlen(cmd) + 2;
        full_path = malloc(len);
        if (!full_path)
            break;

        snprintf(full_path, len, "%s/%s", token, cmd);

        if (is_executable(full_path))
        {
            free(paths);
            return full_path;
        }

        free(full_path);
        token = strtok(NULL, ":");
    }

    free(paths);
    return NULL;
}
