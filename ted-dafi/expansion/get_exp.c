/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_exp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ted-dafi <ted-dafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 11:20:40 by ted-dafi          #+#    #+#             */
/*   Updated: 2022/06/14 12:56:09 by ted-dafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ted_dafi.h"

char	*get_exp(char *var, char **envp)
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
