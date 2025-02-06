# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: peda-cos <peda-cos@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/05 00:59:07 by peda-cos          #+#    #+#              #
#    Updated: 2025/02/06 02:34:14 by peda-cos         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror
SRCS = main.c utils.c routine.c init.c monitor.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) -pthread $(OBJS) -o $(NAME)
	@echo "Compiled: $(NAME)"

%.o: %.c philo.h
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "Compiling: $<"

clean:
	@rm -f $(OBJS)
	@echo "Cleaned: $(OBJS)"

fclean: clean
	@rm -f $(NAME)
	@echo "Cleaned: $(NAME)"

re: fclean all

.PHONY: all clean fclean re
