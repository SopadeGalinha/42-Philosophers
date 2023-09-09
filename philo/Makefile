# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: heolivei <heolivei@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/18 11:25:43 by jhogonca          #+#    #+#              #
#    Updated: 2023/09/08 19:47:35 by heolivei         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 	= philo
SRCS 	= srcs/main.c \
		srcs/routine.c \
		srcs/utils.c \
		srcs/get_left_fork.c \
		srcs/get_right_fork.c \
		srcs/initialization.c \
		srcs/init_philos_array.c \

CC		= cc
OBJS	=	$(SRCS:.c=.o)
CFLAGS	= -Wall -Wextra -Werror -g #-fsanitize=thread
RM 		= rm -f

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -lpthread

re:		fclean all

clean:
	$(RM) $(OBJS)

fclean:	clean
	$(RM) $(NAME)

norm:
	norminette *.h $(SRCS)
