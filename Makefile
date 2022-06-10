CC = cc

NAME = minishell

CFLAGS = -Wall -Werror -Wextra -g -fsanitize=address

SRCS = utils1.c main.c list_func.c split_list.c parsing.c mohamed/error_managment.c \
		mohamed/exit_code.c mohamed/ft_pstrjoin.c mohamed/ft_strchr.c mohamed/here_docs.c \
		mohamed/get_next_line/get_next_line.c mohamed/get_next_line/get_next_line_utils.c

OBJS = $(SRCS:.c=.o)

RM = rm -f

all: $(NAME)

$(NAME):	$(OBJS)
		$(CC) -lreadline -L /Users/msouiyeh/goinfre/.brew/opt/readline/lib  $(OBJS) -o $(NAME)

clean:
		$(RM) $(OBJS) $(B_OBJS)

fclean: clean
		$(RM) $(NAME) $(B_NAME)

re: fclean all

.PHONY: all clean fclean re bonus