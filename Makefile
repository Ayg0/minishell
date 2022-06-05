CC = cc

NAME = minishell

CFLAGS = -Wall -Werror -Wextra -g

SRCS = utils1.c main.c list_func.c split_list.c parsing.c

OBJS = ${SRCS:.c=.o}

RM = rm -f

all: $(NAME)

$(NAME):	$(OBJS)
		$(CC) -lreadline -L /Users/$(USER)/.brew/opt/readline/lib  $(OBJS) -o $(NAME)

clean:
		$(RM) $(OBJS) $(B_OBJS)

fclean: clean
		$(RM) $(NAME) $(B_NAME)

re: fclean all

.PHONY: all clean fclean re bonus