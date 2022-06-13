/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msouiyeh <msouiyeh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 10:14:16 by ted-dafi          #+#    #+#             */
/*   Updated: 2022/06/13 15:51:04 by msouiyeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ted_dafi.h"

char    *get_meta(char *s)
{
    char    *s_se;
    int i;
    int quoted;
    int s_quoted;

    i = ft_strlen(s);
    s_se = ft_calloc(i + 1, sizeof(char));
    i = 0;
    quoted = 0;
    s_quoted = 0;
    while (s[i])
    {
        if (s[i] == '"' && s_quoted == 0)
        {
            quoted = !quoted;
            s_se[i] = 'd';
        }
		else if (s[i] == '\'' && quoted == 0)
        {
            s_quoted = !s_quoted;
            s_se[i] = 's';
        }
        else if (quoted || s_quoted)
            s_se[i] = 'q';
        else
            s_se[i] = decide(" \t\n|<>", "bbbprw", s[i]);
        i++;
    }
    return (s_se);
}

void	proccess_data(t_data *data)
{
	data->meta_str = get_meta(data->cmd);
	data->list = ft_slpit_list(data->meta_str, data->cmd, 'b');
}

void	clear_data(t_data *data)
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
}

int prompt_display(t_data *data, char **envp)
{
    int     i;

	(void)envp;
    write(1, "\e[H\e[2J", 8);
	i = 0;
    while(1)
    {
    	data->cmd = readline("\033[0;34mhalf-bash-3.2$\033[0;37m ");
    	add_history(data->cmd);
		if (*data->cmd == '\0')
			exit(1);
		proccess_data(data);
		if (manage_errors(data) == 0)
			continue ;
		//launch_here_docs(data, envp);
		expand_all(*data, envp);
		clear_data(data);
		//system("leaks minishell");
    }
    return (0);
}
