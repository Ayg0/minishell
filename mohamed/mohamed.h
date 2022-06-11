/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mohamed.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ted-dafi <ted-dafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 14:48:22 by ted-dafi          #+#    #+#             */
/*   Updated: 2022/06/11 14:56:09 by ted-dafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MOHAMED_H
# define MOHAMED_H
# include "../minishell.h"

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

int			manage_errors(t_data *data);
int			*exit_code(void);
void		set_exit_code(int status);
int			get_exit_code(void);
void		launch_here_docs(t_data *data, char **envp);
char		*ft_strdup(char *s1);
#endif
