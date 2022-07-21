/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mohamed.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msouiyeh <msouiyeh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 14:48:22 by ted-dafi          #+#    #+#             */
/*   Updated: 2022/07/21 18:47:34 by msouiyeh         ###   ########.fr       */
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
	char			*old_token;
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

int			ft_wc(char *s, char c);
int			is_true_pip(char *str);
char		*ready_path(char **env, char *cmd);

void		here_doc_parent_wait(int pid);

char		*ult_strjoin(char *s1, char *s2, int flag);
void		fork_print_error(char *error_str);
void		dup_for_built_in(t_pokets	*pokets, int *in, int *out);

int			check_if_in(char *srch_for, char **srch_in);
char		*my_strtrim(char *s1, char *set);

int			is_built_in(char **cmd);
int			is_true_pip(char *str);

void		launch_built_in(int index, t_pokets *poket);

void		free_redirects(t_redirections *redirects);

void		process_av_help(t_tokens **itire, t_pokets *poket);

void		get_redirects_done(t_tokens **itire, t_pokets *poket);

void		handle_sigint(int signum);
void		set_signal_handlers(void);
void		zero_it(char	****envpd, char **envp, t_pokets **pokets);
int			parse_it(t_data *data, t_pokets **pokets, char	***envpd);
void		free_triple_pp(char ***envpd);

void		redirection_error(char *errorstr, int flag);
char		*red_join(char *s1, char *s2);

void		resplit_tokens(t_data	*data);
void		reattach(t_tokens **itire, t_tokens *new);

void		change_in_parrent(t_data *data);
int			launch_helper(t_data *data, char **envp);
void		helper_loop(t_tokens *itire, char *path, char **envp);
void		change_here_doc(t_tokens *itire, char *path);
void		here_doc(int fd, char *limiter, char **envp);

void		go_child(t_pokets *poket);
void		fork_it_helper(t_pokets *itire);
void		fork_print_error(char *error_str);
void		fork_it(t_pokets *pokets);

void		open_redirects(t_pokets *pokets);
int			open_write(t_pokets *pokets);
int			open_read(t_pokets *pokets);
void		unlink_helper(int unlnk, t_redirect *tmp);
void		unlink_here_docs(t_pokets *pokets);

void		ft_perror(char *str);
void		ft_dup(int fd_one, int fd_two);
char		*clean_exit(char *path, char *cmd);
char		*clean_set_up(char *path, char *cmd);
char		*ready_path(char **env, char *cmd);

void		error_print(char *error_str, int len);

void		set_global_error(int error);
int			get_global_error(void);

void		execute_pipline(t_pokets *pokets);
void		handle_sigint(int signum);

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
int			get_global_here_doc(void);
void		set_global_here_doc(int error);
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
