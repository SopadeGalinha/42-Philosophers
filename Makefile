# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jhogonca <jhogonca@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/18 11:25:43 by jhogonca          #+#    #+#              #
#    Updated: 2023/08/24 13:57:47 by jhogonca         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.SILENT:

NAME	 	=	philo

SRCS_LST	=	srcs/main.c srcs/init_table.c \
				srcs/check_args.c srcs/minilibft.c \
				srcs/init_table_utils.c srcs/log_messages.c
				
OBJS_LST	=	$(SRCS_LST:.c=.o)

CC			= cc
CFLAGS		= -Wall -Wextra -Werror -g -L. -lpthread -fsanitize=address
RM 			= rm -f

all:		$(NAME)
	@echo "\033[32m[ ✔ ] $(NAME) ready\033[0m"

$(NAME):	$(OBJS_LST)
			$(CC) $(CFLAGS) $(OBJS_LST) -o $(NAME)

clean:
			$(RM) $(OBJS_LST)
	@echo "\033[31m[ ✔ ] $(NAME) objects removed\033[0m"

fclean:		clean
			$(RM) $(NAME)
	@echo "\033[31m[ ✔ ] $(NAME) removed\033[0m"

re:			fclean all
	@echo "\033[32m[ ✔ ] $(NAME) reloaded\033[0m"

norm:
	norminette $(SRCS_LST) philo.h
	@echo "\033[32m[ ✔ ] Norminette\033[0m"