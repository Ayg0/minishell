/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_re_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ted-dafi <ted-dafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 09:09:19 by msouiyeh          #+#    #+#             */
/*   Updated: 2022/07/01 06:33:44 by ted-dafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ted_dafi.h"

int	search_for_new(char **s, char *new)
{
	int		i;
	char	*tmp;

	i = 0;
	if (!new)
		return (-1);
	while (s[i])
	{
		tmp = ft_substr(new, 0, ft_strchr_null(new, '+', '='));
		if (!ft_strncmp(s[i], tmp, ft_strlen(tmp)))
		{
			free(tmp);
			return (i);
		}
		free(tmp);
		i++;
	}
	return (-1);
}

int	ft_count(char **s, char *new, int *place)
{
	int	i;

	i = 0;
	while (s && s[i])
		i++;
	if (place)
		*place = search_for_new(s, new);
	if (new && (*place == -1))
		i++;
	return (i);
}

char	*str_without_pls(char *new)
{
	int		i;
	int		j;
	char	*result;

	i = ft_strlen(new);
	result = ft_calloc(i, sizeof(char));
	i = 0;
	j = 0;
	while (new[i])
	{
		if (new[i] == '+')
			i++;
		else
			result[j++] = new[i++];
	}
	return (result);
}

char	*add_it(char *old, char *new)
{
	if (ft_strchr(new, '+') && old)
		return (ft_strjoin(old, ft_strchr(new, '=') + 1));
	else if (ft_strchr(new, '+'))
		return (str_without_pls(new));
	return (ft_strdup(new));
}

char	**re_envp(char **envp, int flag, char *new)
{
	int		i;
	char	**final;
	int		place;

	place = -1;
	i = ft_count(envp, new, &place);
	final = ft_calloc(i + 1, sizeof(char *));
	i = 0;
	while (envp && envp[i])
	{
		if (i == place && new)
			final[i] = add_it(envp[i], new);
		else
			final[i] = ft_strdup(envp[i]);
		i++;
	}
	if (new && place == -1)
		final[i] = add_it(NULL, new);
	if (flag)
		free_triple_pp(&envp);
	return (final);
}
