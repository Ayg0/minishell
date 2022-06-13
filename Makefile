CC = cc

NAME = minishell

CFLAGS = -Wall -Werror -Wextra -g 
#-fsanitize=address

GSRCS = global_utils/decide.c global_utils/env_scout.c global_utils/ft_calloc.c			\
		global_utils/ft_strcmp.c global_utils/ft_strjoin.c global_utils/ft_strlcpy.c	\
		global_utils/ft_strlen.c global_utils/ft_substr.c global_utils/ft_strchr.c		\
		global_utils/ft_strdup.c
TSRCS = ted-dafi/split_list.c ted-dafi/parsing.c ted-dafi/expan.c ted-dafi/list_func.c
MSRCS = mohamed/error_managment.c mohamed/exit_code.c mohamed/ft_pstrjoin.c \
		mohamed/get_next_line/get_next_line.c mohamed/get_next_line/get_next_line_utils.c mohamed/here_docs.c

SRCS =  main.c $(TSRCS) $(MSRCS) $(GSRCS)

OBJS = $(SRCS:.c=.o)

RM = rm -f

all: $(NAME)

$(NAME):	$(OBJS)
		$(CC) $(CFLAGS) -lreadline -L /Users/msouiyeh/goinfre/.brew/opt/readline/lib  $(OBJS) -o $(NAME)
#		$(CC) -lreadline -L /Users/$(USER)/.brew/opt/readline/lib  $(OBJS) -o $(NAME)

clean:
		$(RM) $(OBJS) $(B_OBJS)

fclean: clean
		$(RM) $(NAME) $(B_NAME)

re: fclean all

.PHONY: all clean fclean re bonus