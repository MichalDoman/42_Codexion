NAME=codexion
CC=cc
CFLAGS=-Wall -Wextra -Werror -pthread -Iinclude

SRC =	main.c \
		core/parsing/validation.c \
		core/parsing/parsing.c \
		core/simulation/init_simulation.c \
		core/heap/heap.c \
		utils/debugging/print_config.c \
		utils/debugging/print_sim.c \

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)
	
re: fclean all

.PHONY: all clean fclean re