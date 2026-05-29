NAME = unix-shell

CC = gcc
CFLAGS = -Wall -Wextra -Werror -Iinclude -g

SRC = \
    src/core/shell.c \
    src/core/init.c \
    src/core/loop.c \
    src/core/prompt.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -lreadline -o $(NAME)

clean:
	rm -f $(NAME)

re: clean all
