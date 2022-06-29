/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mohamed.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ted-dafi <ted-dafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 14:48:22 by ted-dafi          #+#    #+#             */
/*   Updated: 2022/06/29 22:10:11 by ted-dafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MOHAMED_H
# define MOHAMED_H
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

void		execute_pipline(t_pokets *pokets);

void		global_initializer(void);

char		*mft_strdup(char *str);
t_redirect	*ft_newredi(char *file_name, char type, int code);
t_redirect	*ft_lastredi(t_redirect *lst);
void		ft_rediadd_back(t_redirect	**lst, t_redirect	*new);

void		read_redirect(t_tokens *itire, t_pokets *poket);
void		write_redirect(t_tokens *itire, t_pokets *poket);
void		delet_token(t_tokens **token);
void		process_redirect(t_tokens **itire, t_pokets *poket);

char		*here_doc_join(char *s1, char *s2, int flag);
int			check_name(char	*name, int *i);
char		*final_expand(char *str, int *i, char **envp);
char		*check_and_expand(char *str, char **envp);
char		*remove_limiter_q(char *limiter);
int			check_max_here_doc(t_tokens *itire);

void		clean_big_one(t_pokets *pokets);
int			get_global_error(void);
void		set_global_error(int error);
void		ft_poketadd_back(t_pokets **lst, t_pokets	*new);
void		ft_poketadd_front(t_pokets	**lst, t_pokets	*new);
void		ft_poketsclear(t_pokets **lst, void (*del)(void *));
void		ft_delpoket(t_pokets *lst, void (*del)(void *));
t_pokets	*ft_lastpoket(t_pokets *lst);
t_pokets	*ft_new_poket(char ***env);
int			ft_poketsize(t_pokets *lst);
void		fill_redirections(t_pokets	**pokets, char ***envp, t_data *data);
int			manage_errors(t_data *data);
void		set_exit_code(int status);
int			get_exit_code(void);
void		launch_here_docs(t_data *data, char **envp);
char		*ft_strdup(char *s1);
#endif
