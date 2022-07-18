/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msouiyeh <msouiyeh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 12:43:28 by ted-dafi          #+#    #+#             */
/*   Updated: 2022/07/18 11:22:51 by msouiyeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ted_dafi.h"


char	*get_str(char *s1)
{
	char	*str;
	char	*tmp;

	tmp = getcwd(NULL, 0);
	if (!tmp)
		return (NULL);
	str = ft_strjoin(s1, tmp);
	free(tmp);
	return (str);
}

void	cd(t_pokets *poket)
{
	int		i;
	char	*s1;
	char 	*s2;

	s2 = get_str("OLDPWD=");
	if (!poket->av[1])
		return ;
	i = chdir(poket->av[1]);
	s1 = get_str("PWD=");
	if (i == -1)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(poket->av[1], 2);
		ft_putstr_fd(": ", 2);
		perror(NULL);
		set_exit_code(1);
		set_global_error(1);
	}
	else
	{
		*(poket->env) = re_envp(*(poket->env), 1, s1);
		*(poket->env) = re_envp(*(poket->env), 1, s2);
	}
	if (s1)
		free(s1);
	if (s2)
	free(s2);
}
