/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msouiyeh <msouiyeh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 10:15:08 by ted-dafi          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/06/10 16:28:46 by msouiyeh         ###   ########.fr       */
=======
/*   Updated: 2022/06/10 16:28:46 by msouiyeh         ###   ########.fr       */
>>>>>>> 14c9fbb588c1118901c7b5f9575658ee018653cb
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "mohamed/get_next_line/get_next_line.h"

typedef struct s_list
{
    char			*content;
	struct s_list	*previous;
	struct s_list	*next;
}   t_list;

typedef struct	s_tokens
{
	char			*meta_data;
	char			*token;
	int				max;
	struct s_tokens	*previous;
	struct s_tokens	*next;
}	t_tokens;

typedef struct s_data
{
	char		*cmd;
	char		*meta_str;
	t_tokens	*list;
}   t_data;

typedef struct s_allocated
{
	void	*pointer;
	struct s_allocated	*next;
}	t_allocated;



//mohamed
int			manage_errors(t_data *data);
char		*ft_strchr(const char *s, int c);
int			*exit_code(void);
void		set_exit_code(int status);
int			get_exit_code(void);
void		launch_here_docs(t_data *data, char **envp);
char		*ft_strdup(char *s1);

//taha
void		*ft_calloc(size_t count, size_t size);
char		**ft_split(char *s, char c);
int	    	ft_strlen(char *s);
size_t		ft_strlcpy(char *dest, const char *src, size_t size);
int	    	ft_strcmp(char *s1, char *s2);
int     	prompt_display(t_data *data, char **envp);
void		ft_lstadd_back(t_tokens **lst, t_tokens *new);
t_tokens	*ft_lstnew(t_tokens *previous, void *meta, char *token);
t_tokens	*ft_lstlast(t_tokens *lst);
char		*ft_strjoin(char *s1, char *s2);
char		*ft_substr(char *s, unsigned int start, size_t len);
t_tokens	*ft_slpit_list(char *s, char *s2, char delimiter);
char    	decide(char *s,char *s2, char c);
int			expand_all(t_data data, char **envp);
#endif
