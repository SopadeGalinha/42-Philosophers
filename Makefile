# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jhogonca <jhogonca@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/18 11:25:43 by jhogonca          #+#    #+#              #
#    Updated: 2023/09/23 18:00:25 by jhogonca         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.SILENT:

NAME    = philo

SRCS    = srcs/main.c srcs/init_table.c \
			srcs/check_args.c srcs/actions.c \
			srcs/utils.c srcs/start_dinner.c

OBJS    = $(SRCS:.c=.o)

RM      = rm -f

CC      = gcc

CFLAGS  = -g -Wall -Wextra -Werror -pthread

# LDFLAGS = -fsanitize=thread

$(NAME): $(OBJS)
		@echo "\033[1;36m[ ✔ ] Creating $(NAME)...\033[0m"
		$(CC) $(CFLAGS) $(LDFLAGS) $(OBJS) -o $(NAME)
		@echo "\033[1;32m[ ✔ ] $(NAME) ready\033[0m"

all: $(NAME)

clean:
		$(RM) $(OBJS)
		@echo "\033[1;31m[ ✔ ] $(NAME) objects removed\033[0m"

fclean: clean
		$(RM) $(NAME)
		@echo "\033[1;31m[ ✔ ] $(NAME) executable removed\033[0m"

re: fclean all
		@echo "\033[1;35m[ ✔ ] $(NAME) reloaded\033[0m"

norm:
		@echo "\033[1;3;38;5;206mRunning Norminette...\033[0m"
		norminette $(SRCS) philo.h
		@echo "\033[1;38;5;206m[ ✔ ] Norminette OK\033[0m"

.PHONY: all clean fclean re norm
