/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msouiyeh <msouiyeh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 10:14:16 by ted-dafi          #+#    #+#             */
/*   Updated: 2022/08/01 00:02:00 by msouiyeh         ###   ########.fr       */
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
		i[1] = get_meta_quotes(s[i[0]], &s_quoted, &quoted);
		if (i[1])
			s_se[i[0]] = i[1];
		else if (quoted || s_quoted)
			s_se[i[0]] = 'q';
		else
			s_se[i[0]] = decide(" \t\n|<>", "bbbprw", s[i[0]], 'u');
		i[0]++;
	}
	return (s_se);
}

void	proccess_data(t_data *data)
{
	data->meta_str = get_meta(data->cmd);
	data->list = ft_split_list(data->meta_str, data->cmd, 'b');
}

void	clear_data(t_data *data, t_pokets **pokets, char	***envpd)
{
	void	*tmp;

	if (data->cmd)
		free(data->cmd);
	data->cmd = NULL;
	if (data->meta_str)
		free(data->meta_str);
	data->meta_str = NULL;
	free_triple_pp(envpd);
	while (data->list)
	{
		if (data->list->meta_data)
			free(data->list->meta_data);
		if (data->list->token)
			free(data->list->token);
		if (data->list->old_token)
			free(data->list->old_token);
		tmp = data->list;
		data->list = data->list->next;
		free(tmp);
	}
	clean_big_one(*pokets);
	*pokets = NULL;
}

int	prompt_display(t_data *data, char **envp)
{
	char		***envpd;
	t_pokets	*pokets;

	zero_it(&envpd, envp, &pokets);
	load_history();
	while (-1)
	{
		clear_data(data, &pokets, NULL);
		initialise();
		if (get_global_error() != 0)
			continue ;
		data->cmd = readline("minishell$ ");
		if (data->cmd == NULL)
			(put_history() && resettermios_attr() && \
			(write(1, "exit\n", 5) && my_exit(0, NULL)));
		if (*(data->cmd) == '\0')
			continue ;
		make_history(data->cmd);
		if (parse_it(data, &pokets, envpd) != 0)
			continue ;
		execute_pipline(pokets);
		if (get_global_error() != 0)
			continue ;
	}
	return (0);
}
