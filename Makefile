NAME = unix-shell

CC = gcc
CFLAGS = -Wall -Wextra -Werror -Iinclude -g

SRC = \
    src/core/shell.c \
    src/core/init.c \
    src/core/loop.c \
    src/core/prompt.c \
    src/parse/lexer.c \
    src/parse/parser.c \
    src/parse/command.c \
    src/parse/pipeline.c \
    src/parse/redirection.c \
    src/util/debug.c \
    src/exec/exec_command.c \
    src/exec/exec_pipeline.c \
    src/exec/exec_redirection.c \
    src/builtin/builtin.c \
    src/builtin/pwd.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -lreadline -o $(NAME)

clean:
	rm -f $(NAME)

re: clean all
