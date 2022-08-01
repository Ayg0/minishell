/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msouiyeh <msouiyeh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 09:10:58 by msouiyeh          #+#    #+#             */
/*   Updated: 2022/08/01 06:40:41 by msouiyeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mohamed.h"

void	handle_sigint(int signum)
{
	(void)signum;
	write (1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	set_exit_code(1);
}

void	set_signal_handlers(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}

void	zero_it(char	****envpd, char **envp, t_pokets **pokets)
{
	*pokets = NULL;
	*envpd = ft_calloc(sizeof(char **), 1);
	**envpd = re_envp(envp, 0, NULL);
	set_exit_code(0);
	set_signal_handlers();
}

int	parse_it(t_data *data, t_pokets **pokets, char	***envpd)
{
	proccess_data(data);
	if (manage_errors(data) == 0)
		return (1);
	launch_here_docs(data, *envpd);
	if (get_global_error() != 0)
		return (1);
	expand_all(data, *envpd);
	fill_redirections(pokets, envpd, data);
	return (0);
}

void	free_triple_pp(char ***envpd)
{
	char	**tmp;

	if (!envpd)
		return ;
	tmp = *envpd;
	while (*envpd && **envpd)
	{
		free(**envpd);
		(*envpd)++;
	}
	free (tmp);
}
