SRCS			= main.c \

OBJS			= $(SRCS:.c=.o)
CC				= cc
CFLAGS			= -Wall -Wextra -Werror
LIBCR			= ar rc
RM				= rm -f

NAME			= philo

all:			$(NAME)

$(NAME):	$(OBJS)
			$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
clean:
			$(RM) $(OBJS)
fclean:		clean
			$(RM) $(NAME)

re:			fclean all