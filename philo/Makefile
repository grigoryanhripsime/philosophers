CC = cc

CFLAGS = -Wall -Wextra -Werror -I ./ # -g -pthread -fsanitize=thread

NAME = philo

SRCS = philosophers.c utils.c init.c routine.c

OBJS = $(SRCS:.c=.o)


all: $(NAME)

$(NAME): $(OBJS) Makefile philosophers.h
	$(CC) $(CFLAGS) $(OBJS) -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean 
	rm -f $(NAME)

re: fclean all

.PHONY: all fclean clean re