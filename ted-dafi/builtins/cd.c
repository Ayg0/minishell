/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ted-dafi <ted-dafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 12:43:28 by ted-dafi          #+#    #+#             */
/*   Updated: 2022/08/06 09:01:47 by ted-dafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ted_dafi.h"

int	cd_error(t_pokets *poket, int err)
{
	char	*tmp;
	char	*tmp2;

	tmp2 = NULL;
	if (err == -1)
	{
		if (poket->av[1])
			tmp2 = ft_strdup(poket->av[1]);
		else
			tmp2 = get_exp(ft_strdup("HOME"), 'q', *poket->env);
		tmp = re_join(ft_strdup("minishell: cd: "), tmp2);
		perror(tmp);
		free(tmp);
	}
	else
		ft_putstr_fd(ft_strdup("minishell: cd: HOME not set\n"), 2);
	set_exit_code(1);
	set_global_error(1);
	return (1);
}

char	*get_oldpwd(t_pokets *poket)
{
	int	place;

	place = -1;
	ft_count(*poket->env, "PWD", &place);
	if (place == -1)
		return (re_join(ft_strdup("OLDPWD="), getcwd(NULL, 0)));
	return(re_join(ft_strdup("OLDPWD="), get_exp(ft_strdup("PWD"), 'q', *poket->env)));
}

int	set_env_path(t_pokets *poket, char *pwd, char *oldpwd)
{
	int	index;

	index = -1;
	ft_count(*poket->env, "PWD", &index);
	if (index != -1)
		*(poket->env) = re_envp(*(poket->env), 1, pwd);
	index = -1;
	ft_count(*poket->env, "OLDPWD", &index);
	if (index != -1)
		*(poket->env) = re_envp(*(poket->env), 1, oldpwd);
	return (0);
}

int	change_to_home(t_pokets *poket)
{
	int		index;
	char	*tmp;

	index = -1;
	ft_count(*poket->env, "HOME", &index);
	if (index == -1)
		return (-2);
	tmp = get_exp(ft_strdup("HOME"), 'q', *poket->env);
	if (tmp && !ft_strlen(tmp))
	{
		free(tmp);
		tmp = ft_strdup(".");
	}
	index = chdir(tmp);
	free(tmp);
	return (index);
}

int	change_dir(t_pokets *poket)
{
	int	err;

	err = 0;
	if (!poket->av[1])
		err = change_to_home(poket);
	else
		err = chdir(poket->av[1]);
	return (err);
}

void	cd(t_pokets *poket)
{
	char	*oldpwd;
	char	*pwd;
	int		err;

	oldpwd = get_oldpwd(poket);
	err = change_dir(poket);
	pwd = re_join(ft_strdup("PWD="), getcwd(NULL, 0));
	if (err < 0)
		cd_error(poket, err);
	else
		set_env_path(poket, pwd, oldpwd);
	free(pwd);
	free(oldpwd);
}