/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expan.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ted-dafi <ted-dafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 10:52:56 by ted-dafi          #+#    #+#             */
/*   Updated: 2022/06/11 14:41:16 by ted-dafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ted_dafi.h"

char *get_exp(char *var, char **envp)
{
	int	i;
	int	j;

	if (!envp)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		j = env_scout(envp[i], var);
		if (j != -1)
		{
			free(var);
			return (ft_substr(envp[i], j, ft_strlen(envp[i]) - j));
		}
		i++;
	}
	free(var);
	return (NULL);
}

char	*expand(t_tokens *list, char **envp)
{
	int		i;
	int		j;
	int		flag[2];
	char	*str;

	i = 0;
	flag[0] = 0;
	flag[1] = 0;
	str = NULL;
	while (list->token[i])
	{
		if (list->meta_data[i] == 'd' && !flag[1])
			flag[0] = !flag[0];
		if (list->meta_data[i] == 's' && !flag[0])
			flag[1] = !flag[1];
		if (list->token[i] == '$' && !flag[1])
		{
			j = i;
			while (list->token[i] && list->token[i] != ' ' && list->token[i] != '\"' && list->token[i] != '\'')
				i++;
			str = ft_strjoin(str, get_exp(ft_substr(list->token, j + 1, j - i - 1), envp));
		}
		str = ft_strjoin(str, ft_substr(list->token, i, 1));
		i++;
	}
	if (!ft_strlen(str))
	{
		free (str);
		return (NULL);
	}
	return(str);
}

int	expand_all(t_data data, char **envp)
{
	while (data.list)
	{	
		char *str = expand(data.list, envp);
		printf("%s\n", str);
		free(str);
		data.list = data.list->next;
	}
	return (0);
}