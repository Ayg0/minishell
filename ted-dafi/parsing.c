/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msouiyeh <msouiyeh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 10:14:16 by ted-dafi          #+#    #+#             */
/*   Updated: 2022/06/27 22:53:59 by msouiyeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ted_dafi.h"

char	get_meta_quotes(char c, int *s_quoted, int *quoted)
{
	if (c == '"' && *s_quoted == 0)
	{
		*quoted = !(*quoted);
		return ('d');
	}
	else if (c == '\'' && *quoted == 0)
	{
		*s_quoted = !(*s_quoted);
		return ('s');
	}
	return (0);
}

char	*get_meta(char *s)
{
	char	*s_se;
	int		i[2];
	int		quoted;
	int		s_quoted;

	if (!s)
		return (NULL);
	s_se = ft_calloc(ft_strlen(s) + 1, sizeof(char));
	i[0] = 0;
	quoted = 0;
	s_quoted = 0;
	while (s[i[0]])
	{
		i[1] = get_meta_quotes(s[i[0]], &quoted, &s_quoted);
		if (i[1])
			s_se[i[0]] = i[1];
		else if (quoted || s_quoted)
			s_se[i[0]] = 'q';
		else
			s_se[i[0]] = decide(" \t\n|<>", "bbbprw", s[i[0]]);
		i[0]++;
	}
	return (s_se);
}

void	proccess_data(t_data *data)
{
	data->meta_str = get_meta(data->cmd);
	data->list = ft_split_list(data->meta_str, data->cmd, 'b');
}

void	clear_data(t_data *data, t_pokets *pokets)
{
	void	*tmp;

	free(data->cmd);
	free(data->meta_str);
	while (data->list)
	{
		free(data->list->meta_data);
		free(data->list->token);
		tmp = data->list;
		data->list = data->list->next;
		free(tmp);
	}
	clean_big_one(pokets);
}

int	prompt_display(t_data *data, char **envp)
{
	t_pokets	*pokets;
	int			i;

	write(1, "\e[H\e[2J", 8);
	pokets = NULL;
	i = 0;
	while (1)
	{
		clear_data(data);
		data->cmd = readline("\033[0;34mhalf-bash-3.2$\033[0;37m ");
		add_history(data->cmd);
		if (*data->cmd == '\0')
			exit(1);
		proccess_data(data);
		if (manage_errors(data) == 0)
			continue ;
		launch_here_docs(data, envp);
		expand_all(data, envp);
		fill_redirections(&pokets, envp, data);
		// while (data->list)
		// {
		// 	printf("%s ---> ", data->list->meta_data);
		// 	printf("%s\n", data->list->token);
		// 	data->list = data->list->next;
		// }
		// system("leaks minishell");
	}
	return (0);
}
