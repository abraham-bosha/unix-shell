#ifndef SHELL_H
#define SHELL_H

typedef struct shell
{
    char *oldpwd;
    int last_exit_status;
} shell_t;

extern shell_t *shell;

int shell_init(void);
void shell_loop(void);

#endif

