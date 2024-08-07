CC = cc

CFLAGS = -Wall -Wextra -Werror -I ./

NAME = philo_bonus

SRCS = philosophers_bonus.c utils_bonus.c init_bonus.c routine_bonus.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) Makefile philosophers_bonus.h
	$(CC) $(CFLAGS) $(OBJS) -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean 
	rm -f $(NAME)

re: fclean all

.PHONY: all fclean clean re