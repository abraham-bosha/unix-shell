NAME = unix-shell

CC = gcc
CFLAGS = -Wall -Wextra -Werror -Iinclude -g

SRC = src/core/shell.c
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(NAME)

clean:
	rm -f $(NAME)

re: clean all
