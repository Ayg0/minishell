/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ted_dafi.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msouiyeh <msouiyeh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 14:33:24 by ted-dafi          #+#    #+#             */
/*   Updated: 2022/06/30 17:58:47 by msouiyeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TED_DAFI_H
# define TED_DAFI_H
# include "../minishell.h"

# ifndef S_REDIRECT
#  define S_REDIRECT

typedef struct s_redirect
{
	char				*file_name;
	char				type;
	int					code;
	struct s_redirect	*next;
}	t_redirect;
# endif

# ifndef S_REDIRECTIONS
#  define S_REDIRECTIONS

typedef struct s_redirections
{
	t_redirect	*read;
	t_redirect	*write;
}	t_redirections;
# endif

# ifndef S_POKETS
#  define S_POKETS

typedef struct s_pokets
{
	int				index;
	int				flag;
	int				last_pid;
	int				pip[2];
	int				outfile_fd;
	int				infile_fd;
	char			**av;
	char			***env;
	char			*path;
	t_redirections	*redirects;
	struct s_pokets	*next;
	struct s_pokets	*prev;
}	t_pokets;
# endif

# ifndef S_TOKEN
#  define S_TOKEN

typedef struct s_tokens
{
	char			*meta_data;
	char			*token;
	int				flag;
	int				max;
	struct s_tokens	*previous;
	struct s_tokens	*next;
}	t_tokens;
# endif

# ifndef S_DATA
#  define S_DATA

typedef struct s_data
{
	char		*cmd;
	char		*meta_str;
	t_tokens	*list;
}	t_data;
# endif

void		echo(t_pokets *poket);
void		cd(t_pokets *poket);
void		pwd(t_pokets *poket);
void		export(t_pokets *poket);
void		unset(t_pokets *poket);
void		env(t_pokets *poket);
void		ft_exit(t_pokets *poket);

void		proccess_data(t_data *data);
char		**re_envp(char **envp, char *new);
int			ft_strlen(char *s);
int			ft_strcmp(char *s1, char *s2);
int			prompt_display(t_data *data, char **envp);
void		remove_quotes(t_data *data);
void		ft_lstadd_back(t_tokens **lst, t_tokens *new);
t_tokens	*ft_lstnew(t_tokens *previous, char *meta, char *token);
t_tokens	*ft_lstlast(t_tokens *lst);
char		*ft_strjoin(char *s1, char *s2);
t_tokens	*ft_split_list(char *s, char *s2, char delimiter);
int			expand_all(t_data *data, char **envp);
char		*re_join(char *s1, char *s2);
char		**re_envp(char **envp, char *new);
void		free_triple_pp(char ***envpd);
char		*get_meta(char *s);
void		set_variable(char *value);
char		*get_variable(void);
char		*get_exp(char *var, char c, char **envp);
#endif