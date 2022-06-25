/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mohamed.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msouiyeh <msouiyeh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 14:48:22 by ted-dafi          #+#    #+#             */
/*   Updated: 2022/06/25 16:17:43 by msouiyeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MOHAMED_H
# define MOHAMED_H
# include "../minishell.h"

#ifndef S_READ
# define S_READ
typedef struct s_read
{
	char			*file_name;
	char			type;
	struct s_read	*next;
}	t_read;
#endif

#ifndef S_WRITE
# define S_WRITE
typedef struct s_write
{
	char			*file_name;
	int				code;
	struct s_write	*next;
}	t_write;
#endif

#ifndef S_REDIRECTIONS
# define S_REDIRECTIONS
typedef struct s_redirections
{
	t_read	*read;
	t_write	*write;
	
}	t_redirections;
#endif

#ifndef S_POKETS
# define S_POKETS
typedef struct s_pokets
{
	int				index;
	int				last_pid;
	int				pip[2];
	int				outfile_fd;
	int				infile_fd;
	char			**av;
	char			**env;
	char			*path;
	t_redirections	*redirects;
	struct s_pokets	*next;
	struct s_pokets	*prev;
}	t_pokets;
#endif



#ifndef S_TOKEN
# define S_TOKEN
typedef struct	s_tokens
{
	char			*meta_data;
	char			*token;
	int				max;
	struct s_tokens	*previous;
	struct s_tokens	*next;
}	t_tokens;
#endif

#ifndef S_DATA
# define S_DATA
typedef struct s_data
{
	char		*cmd;
	char		*meta_str;
	t_tokens	*list;
}   t_data;
#endif

void		ft_poketadd_back(t_pokets **lst, t_pokets	*new);
void		ft_poketadd_front(t_pokets	**lst, t_pokets	*new);
void		ft_poketsclear(t_pokets **lst, void (*del)(void *));
void		ft_delpoket(t_pokets *lst, void (*del)(void *));
t_pokets	*ft_lastpoket(t_pokets *lst);
t_pokets	*ft_new_poket(char **env);
int			ft_poketsize(t_pokets *lst);
void		fill_redirections(t_pokets	*pokets, char **envp, t_data *data);
int			manage_errors(t_data *data);
int			*exit_code(void);
void		set_exit_code(int status);
int			get_exit_code(void);
void		launch_here_docs(t_data *data, char **envp);
char		*ft_strdup(char *s1);
#endif
