NAME=codexion
CC=cc
CFLAGS=-Wall -Wextra -Werror -pthread -Iinclude

SRC =	main.c \
		src/parsing/validation.c \
		src/parsing/parsing.c \
		src/core/simulation/simulation_init.c \
		src/core/simulation/simulation_core.c \
		src/core/simulation/simulation_misc.c \
		src/core/threads.c \
		src/core/monitor.c \
		src/core/dongle.c \
		src/core/coder/coder_routine.c \
		src/core/coder/coder_queue.c \
		src/core/coder/coder_misc.c \
		src/core/time.c \
		src/heap/heap.c \
		src/heap/heap_utils.c \

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