/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ted-dafi <ted-dafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 10:14:16 by ted-dafi          #+#    #+#             */
/*   Updated: 2022/06/06 10:28:43 by ted-dafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

// int prompt_display(char **env)
// {
//     int i;
//     char **o;

//     o = malloc(sizeof(char*) * 4);
//     o[0] = "bash";
//     o[1] = "-c";
//     o[3] = '\0';
//     write(1, "\e[H\e[2J", 8);
//     while(1)
//     {
//         write(1, "half-bash-3.2$ ", 16);
//         char    s[1000000] = {};
//         i = 0;
//         while (i == 0 || s[i - 1] != '\n'){
//             read(1, &s[i], 1);i++;}
//         o[2] = s;
//         if (!fork())
//             execve("/bin/bash", o, env);
//         wait(NULL);
//     }
//     return (0);
// }

char    decide(char *s,char *s2, char c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (c == s[i])
			return (s2[i]);
		i++;
	}
	return ('u');
}

char    *get_meta(char *s)
{
    char    *s_se;
    int i;
    int quoted;
    int s_quoted;

    i = ft_strlen(s);
    s_se = ft_calloc(i, sizeof(char));
    i = 0;
    quoted = 0;
    s_quoted = 0;
    while (s[i])
    {
        if (s[i] == '"')
        {
            quoted = !quoted;
            s_se[i] = 'd';
        }
		else if (s[i] == '\'')
        {
            s_quoted = !s_quoted;
            s_se[i] = 's';
        }
        else if (quoted || s_quoted)
            s_se[i] = 'q';
        else
            s_se[i] = decide("\"' \t\n|<>", "dsbbbprw", s[i]);
        i++;
    }
	s_se[i] = 0;
    return (s_se);
}

char	*ft_substr(char *s, unsigned int start, size_t len)
{
	char	*p;
	size_t	i;
	size_t	c;

	i = 0;
	if (!s)
		return (NULL);
	c = ft_strlen(s);
	if (len > c)
		len = c;
	p = (char *)ft_calloc((len + 1), sizeof(char));
	if (!p)
		return (NULL);
	if (start <= c)
	{
		while (s[i + start] && len)
		{
			p[i] = s[ i + start];
			i++;
			len--;
		}
	}
	return (p);
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

	(void) envp;
    write(1, "\e[H\e[2J", 8);
	i = 0;
    while(1)
    {
    	data->cmd = readline("\033[0;34mhalf-bash-3.2$\033[0;37m ");
    	add_history(data->cmd);
		if (*data->cmd == '\0')
			exit(1);
		proccess_data(data);
		clear_data(data);
		system("leaks minishell");
    }
    return (0);
}
