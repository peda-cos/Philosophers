NAME = philo_bonus
CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread
SRCS = main_bonus.c parse_bonus.c init_bonus.c routine_bonus.c actions_bonus.c monitor_bonus.c time_bonus.c utils_bonus.c cleanup_bonus.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS)
	@echo "philo_bonus"

%.o: %.c philo_bonus.h
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "Compiling $<"

clean:
	@rm -f $(OBJS)
	@echo "Objects removed."

fclean: clean
	@rm -f $(NAME)
	@echo "Executable removed."

re: fclean all

.PHONY: all clean fclean re
