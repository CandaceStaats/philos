NAME = philo

CC = gcc
CFLAGS = -Wall -Wextra -Werror
#-g fsanitize=address
#-g fsanitize=thread
SRCS = main.c states.c errorchecks.c sims.c \
actions.c utils.c contutils.c 


OBS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBS)
	$(CC) -o $(NAME) $(OBS)

%.o: %.c philo.h
	$(CC) -c $(CFLAGS) $<

clean:
	rm -f $(OBS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

test: all
	gcc main.c -L. -lphilo 