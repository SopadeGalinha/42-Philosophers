# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: heolivei <heolivei@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/18 11:25:43 by jhogonca          #+#    #+#              #
#    Updated: 2023/08/21 21:49:29 by heolivei         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 	= philo
SRCS 	= srcs/main.c \
		srcs/minilibft.c \
		srcs/initialization.c

CC		= cc
CFLAGS	= -Wall -Wextra -Werror -g
RM 		= rm -f

all: $(NAME)

$(NAME):
	$(CC) $(CFLAGS) $(SRCS) -o $(NAME) -lpthread

re:		fclean all

clean:
	$(RM)

fclean:	clean
	$(RM) $(NAME)

norm:
	norminette *.h $(SRCS)
