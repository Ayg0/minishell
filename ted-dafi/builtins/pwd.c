/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ted-dafi <ted-dafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 14:34:13 by ted-dafi          #+#    #+#             */
/*   Updated: 2022/07/15 12:31:47 by ted-dafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ted_dafi.h"

char	*get_pwd(char **envp)
{
	int	i;
	int	j;

	i = 0;
	while (envp[i])
	{
		j = ft_strncmp(envp[i], "PWD=", ft_strlen("PWD="));
		if (!j)
		{
			while (envp[i][j] != '=')
				j++;
			j++;
			return (&envp[i][j]);
		}
		i++;
	}
	return (NULL);
}

void	pwd(t_pokets *poket)
{
	char	*s;

	(void) poket;
	s = getcwd(NULL, 0);
	if (!s)
		printf("%s\n", get_pwd(*(poket->env)));
	else
		printf("%s\n", s);
	if (s)
		free(s);
}
