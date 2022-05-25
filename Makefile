CC = cc

NAME = minishell

USER = ted-dafi

CFLAGS = -Wall -Werror -Wextra -I/Users/$(USER)/.brew/opt/readline/include

SRCS = ft_split.c parsing.c utils1.c main.c

OBJS = ${SRCS:.c=.o}

RM = rm -f

all: $(NAME)

$(NAME):	$(OBJS)
		$(CC) -lreadline -L /Users/$(USER)/.brew/opt/readline/lib $(OBJS) -o $(NAME)

clean:
		$(RM) $(OBJS) $(B_OBJS)

fclean: clean
		$(RM) $(NAME) $(B_NAME)

re: fclean all

.PHONY: all clean fclean re bonus