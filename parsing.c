/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ted-dafi <ted-dafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 10:14:16 by ted-dafi          #+#    #+#             */
/*   Updated: 2022/06/04 13:43:31 by ted-dafi         ###   ########.fr       */
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

char    decide(char c)
{
    if (c == ' ' || c == '\t')
        return ('b');
    else if (c == '|')
        return ('p');
    else
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
            s_se[i] = decide(s[i]);
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

char	*get_token(t_data *data, int str_num)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (str_num > 0)
	{
		i += len;
		while (data->meta_str[i] && data->meta_str[i] == 'b')
			i++;
		len = 0;
		while (data->meta_str[i + len] && data->meta_str[i + len] != 'b')
			len++;
		str_num--;
	}
	return (ft_substr(data->cmd, i, len));
}

char	*ft_strdup(char *s1)
{
	size_t		i;
	char		*bo;

	i = ft_strlen(s1);
	bo = (char *)ft_calloc(i + 1, sizeof(char));
	if (bo == 0)
		return (0);
	i = 0;
	while (s1[i])
	{
		bo[i] = s1[i];
		i++;
	}
	return (bo);
}

//int	clear_list(t_data	*data)
//{
//	while (data->tokens)
//	{
//		free(data->tokens->s);
//		free(data->tokens);
//		data->tokens = data->tokens->next;
//	}
//	while (data->meta)
//	{
//		free(data->meta);
//		data->meta = data->meta->next;
//	}
//	free(data->cmd);
//	free(data->meta_str);
//	data->tokens = NULL;
//	data->meta = NULL;
//	return (0);
//}

void	proccess_data(t_data *data)
{
	data->meta_str = get_meta(data->cmd);
	data->list = ft_slpit_list(data->meta_str, data->cmd, 'b');
	while (data->list)
	{
		printf("%s::%s\n", data->list->token, data->list->meta_data);
		data->list = data->list->next;
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
    	data->cmd = readline("half-bash-3.2$ ");
    	add_history(data->cmd);
		if (*data->cmd == '\0')
			exit(1);
		proccess_data(data);
    }
    return (0);
}
