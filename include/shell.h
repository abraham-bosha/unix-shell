#ifndef SHELL_H
#define SHELL_H

typedef struct shell
{
    int last_status;
} shell_t;

extern shell_t *shell;

int shell_init(void);
void shell_loop(void);

#endif

