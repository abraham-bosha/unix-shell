NAME = unix-shell

DEBUG ?= 0

CC = gcc
CFLAGS = -Wall -Wextra -Werror -Iinclude -g

ifeq ($(DEBUG),1)
    CFLAGS += -DDEBUG
endif

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
    src/exec/exec_path.c \
    src/exec/exec_command.c \
    src/exec/exec_pipeline.c \
    src/exec/exec_redirection.c \
    src/builtin/builtin.c \
    src/builtin/pwd.c \
    src/builtin/exit.c \
    src/builtin/cd.c \
    src/expand/expand.c 

OBJ = $(SRC:.c=.o)

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -lreadline -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
