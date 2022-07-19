/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ted-dafi <ted-dafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 14:34:13 by ted-dafi          #+#    #+#             */
/*   Updated: 2022/07/19 12:57:28 by ted-dafi         ###   ########.fr       */
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
	return ("Can't retreve current working directory\n");
}

void	pwd(t_pokets *poket)
{
	char	*s;

	(void) poket;
	s = getcwd(NULL, 0);
	if (!s)
		ft_putstr_fd2(ft_strjoin(get_pwd(*(poket->env)), "\n"), 1);
	else
		ft_putstr_fd2(re_join(s, ft_strdup("\n")), 1);
	set_exit_code(0);
	set_global_error(0);
}
