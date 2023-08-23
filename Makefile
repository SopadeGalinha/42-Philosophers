# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jhogonca <jhogonca@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/18 11:25:43 by jhogonca          #+#    #+#              #
#    Updated: 2023/08/23 09:50:54 by jhogonca         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.SILENT:

NAME 	= philo

SRCS 	= srcs/main.c srcs/init_table.c srcs/check_args.c srcs/minilibft.c srcs/init_table_utils.c

CC		= cc
CFLAGS	= -Wall -Wextra -Werror -g -L. -lpthread
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