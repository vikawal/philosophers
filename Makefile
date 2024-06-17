NAME = philo
FLAGS = -Wall -Wextra -Werror -Ofast -o3 -pthread #-g -fsanitize=thread
HEADER = philo.h

SRCS = \
philo_main.c \
start_init.c \
utils.c \
thread_start.c \
act_routine.c \
check.c


OBJS = $(SRCS:.c=.o)


all: $(NAME)

$(NAME): $(OBJS) 
	cc $(OBJS) $(FLAGS) -o $(NAME)



%.o: %.c
	cc $(FLAGS) -c $< -o $@

clean: 
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME) 

re: fclean all

# test: all
# 	./$(NAME)


.PHONY: all clean fclean re test