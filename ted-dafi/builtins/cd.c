/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ted-dafi <ted-dafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 12:43:28 by ted-dafi          #+#    #+#             */
/*   Updated: 2022/07/26 22:08:37 by ted-dafi         ###   ########.fr       */
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

int	cd_error(t_pokets *poket)
{
	char	*tmp;

	tmp = re_join(ft_strdup("minishell: cd: "), ft_strdup(poket->av[1]));
	perror(tmp);
	free(tmp);
	set_exit_code(1);
	set_global_error(1);
	return (1);
}

char	*change(char *av)
{
	char	*s;

	s = getenv("HOME");
	if (!s)
		return (ft_strdup(av));
	if (*av == '~')
		return (re_join(ft_strdup(s), ft_strdup(av + 1)));
	return (ft_strdup(av));
}

void	cd(t_pokets *poket)
{
	int		i;
	char	*s1;
	char	*tmp;
	char	*s2;

	s2 = get_str("OLDPWD=");
	if (!poket->av[1])
		return ;
	tmp = change(poket->av[1]);
	i = chdir(tmp);
	free (tmp);
	s1 = get_str("PWD=");
	if (i == -1)
		cd_error(poket);
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
