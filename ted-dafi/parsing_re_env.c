/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_re_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ted-dafi <ted-dafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 09:09:19 by msouiyeh          #+#    #+#             */
/*   Updated: 2022/08/13 12:14:31 by ted-dafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ted_dafi.h"

int	search_for_new(char **s, char *new)
{
	int		i;
	char	*tmp;
	char	*tmp2;

	i = 0;
	if (!new)
		return (-1);
	while (s[i])
	{
		tmp = ft_substr(new, 0, ft_strchr_null(new, '+', '='));
		tmp2 = ft_substr(s[i], 0, ft_strchr_null(s[i], '+', '='));
		if (!ft_strcmp(tmp2, tmp))
		{
			free(tmp2);
			free(tmp);
			return (i);
		}
		free(tmp2);
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
	int		k;
	char	*result;

	i = ft_strlen(new);
	result = ft_calloc(i, sizeof(char));
	i = 0;
	j = 0;
	k = 0;
	while (new[i])
	{
		if (new[i] == '+' && !k)
		{
			k = 1;
			i++;
		}
		else
			result[j++] = new[i++];
	}
	return (result);
}

char	*add_it(char *old, char *new)
{
	char	*s1;
	char	*s2;

	s1 = ft_strchr(new, '+');
	s2 = ft_strchr(new, '=');
	if (s1 && s2 && s1 - s2 <= 0 && old)
		return (ft_strjoin(old, ft_strchr(new, '=')
				+ (ft_strchr(old, '=') != NULL)));
	else if (s1 && s2 && s1 - s2 <= 0)
		return (str_without_pls(new));
	if (old && !s2)
		return (ft_strdup(old));
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
		{
			final[i] = add_it(envp[i], new);
		}
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
