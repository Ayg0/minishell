/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_re_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msouiyeh <msouiyeh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 09:09:19 by msouiyeh          #+#    #+#             */
/*   Updated: 2022/06/30 09:14:55 by msouiyeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ted_dafi.h"

int	ft_count(char **s, char *new)
{
	int	i;

	i = 0;
	while (s && s[i])
		i++;
	if (new)
		i++;
	return (i);
}

char	**re_envp(char **envp, char *new)
{
	int		i;
	char	**final;

	i = ft_count(envp, new);
	final = ft_calloc(i + 1, sizeof(char *));
	i = 0;
	while (envp && envp[i])
	{
		final[i] = ft_strdup(envp[i]);
		i++;
	}
	if (new)
		final[i] = new;
	return (final);
}
