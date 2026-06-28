NAME=codexion
CC=cc
FLAGS=-Wall -Wextra -Werror -pthread

SRC =	main.c \
		parsing/validation.c \
		parsing/parsing.c \
		utils/debugging/print_config.c \

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)
	
re: fclean all

.PHONY: all clean fclean re