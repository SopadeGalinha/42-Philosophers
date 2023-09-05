# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: heolivei <heolivei@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/18 11:25:43 by jhogonca          #+#    #+#              #
#    Updated: 2023/09/03 11:24:41 by heolivei         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 	= philo
SRCS 	= srcs/main.c \
		srcs/routine.c \
		srcs/minilibft.c \
		srcs/initialization.c \
		srcs/init_philos_array.c

CC		= cc
CFLAGS	= -Wall -Wextra -Werror -g -fsanitize=leak
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
