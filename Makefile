CC = cc 

NAME = minishell

# /Users/msouiyeh/goinfre/.brew/opt/readline/include
# /Users/$(USER)/.brew/opt/readline/include
CFLAGS = -Wall -Werror -Wextra -g  -I /Users/$(USER)/.brew/opt/readline/include

GSRCS = global_utils/decide.c global_utils/env_scout.c global_utils/ft_calloc.c			  	\
		global_utils/ft_strcmp.c global_utils/ft_strjoin.c global_utils/ft_strlcpy.c	  	\
		global_utils/ft_strlen.c global_utils/ft_substr.c global_utils/ft_strchr.c		  	\
		global_utils/ft_strdup.c global_utils/ft_isalnum.c global_utils/ft_isalpha.c 	  	\
		global_utils/ft_isascii.c global_utils/ft_isdigit.c global_utils/ft_isprint.c	  	\
		global_utils/ft_putchar_fd.c  global_utils/ft_putendl_fd.c  global_utils/ft_atoi.c	\
		global_utils/ft_putnbr_fd.c  global_utils/ft_putstr_fd.c global_utils/ft_itoa.c 	\
		global_utils/ft_strncmp.c	global_utils/ft_split.c

TEXP  = ted-dafi/expansion/expan.c ted-dafi/expansion/re_join.c ted-dafi/expansion/get_exp.c \
		ted-dafi/expansion/quote_rm.c
HISRC = ted-dafi/history/get_next_line.c ted-dafi/history/get_next_line_utils.c				\
		ted-dafi/history/history.c

TBUILTINS = ted-dafi/builtins/cd.c ted-dafi/builtins/echo.c ted-dafi/builtins/env.c		\
			ted-dafi/builtins/exit.c ted-dafi/builtins/export.c ted-dafi/builtins/pwd.c	\
			ted-dafi/builtins/unset.c ted-dafi/builtins/unset_valid.c 					\
			ted-dafi/builtins/util_export.c ted-dafi/builtins/more_to_handle.c			\
			ted-dafi/builtins/history.c ted-dafi/builtins/cd_error.c

TGSRC = ted-dafi/split_list.c ted-dafi/parsing.c ted-dafi/list_func.c ted-dafi/parsing_re_env.c


TSRCS = $(TEXP) $(TBUILTINS) $(TGSRC) $(HISRC)


MSRCS = mohamed/error_managment.c mohamed/exit_code.c 	mohamed/ft_pstrjoin.c \
		mohamed/here_docs.c mohamed/redirections.c 		mohamed/redirections_lst_utils.c\
		mohamed/lst_functions/ft_lstadd_back_bonus.c  	mohamed/lst_functions/ft_lstadd_front_bonus.c \
		mohamed/lst_functions/ft_lstlast_bonus.c		mohamed/here_doc_expand.c\
		mohamed/lst_functions/ft_lstnew_bonus.c			mohamed/lst_functions/ft_lstsize_bonus.c	\
		mohamed/here_doc_q_remov.c						mohamed/redirects_processing.c \
		mohamed/execute.c								mohamed/global_error_var.c	\
		mohamed/error_managment_utils.c					mohamed/execute_utils.c		\
		mohamed/execute_redicts.c						mohamed/execute_fork_child.c	\
		mohamed/here_doc_fork.c							mohamed/re_split.c	\
		mohamed/redirectl_process_utils.c				mohamed/parsing_utils.c	\
		mohamed/process_av_utils.c						mohamed/set_built_in.c	\
		mohamed/fork_print_error.c						mohamed/ready_path.c	\
		mohamed/big_one_cleaner.c 						mohamed/termios.c		\
		mohamed/split_reworked.c
		
		

SRCS =  main.c $(TSRCS) $(MSRCS) $(GSRCS)

OBJS = $(SRCS:.c=.o)

RM = rm -f

all: $(NAME)

$(NAME):	$(OBJS)
			@$(CC) $(CFLAGS) -lreadline -L /Users/$(USER)/.brew/opt/readline/lib $(OBJS) -o $(NAME)
#			@$(CC) $(CFLAGS) -lreadline -L /Users/msouiyeh/goinfre/.brew/opt/readline/lib $(OBJS) -o $(NAME)

clean:
		@$(RM) $(OBJS) $(B_OBJS)

fclean: clean
		@$(RM) $(NAME) $(B_NAME)

re: fclean all

.PHONY: all clean fclean re bonus
