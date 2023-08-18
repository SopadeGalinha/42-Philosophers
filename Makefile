# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jhogonca <jhogonca@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/18 11:25:43 by jhogonca          #+#    #+#              #
#    Updated: 2023/08/18 12:57:25 by jhogonca         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 	= philo
SRCS 	= srcs/main.c srcs/minilibft.c srcs/initialization.c

CC		= cc
CFLAGS	= -Wall -Wextra -Werror -g -L.
RM 		= rm -f

all: $(NAME)

$(NAME):
	$(CC) $(CFLAGS) $(SRCS) -o $(NAME)

re:		fclean all

clean:
	$(RM)

fclean:	clean
	$(RM) $(NAME)

norm:
	norminette *.h $(SRCS)