/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ready_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msouiyeh <msouiyeh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 21:02:51 by msouiyeh          #+#    #+#             */
/*   Updated: 2022/08/04 01:30:23 by msouiyeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mohamed.h"

char	*ready_path(char **env, char *cmd)
{
	char	**path;

	if (ft_strchr(cmd, '/') && access(cmd, F_OK) == 0)
		return (clean_exit(cmd, cmd));
	else if (ft_strchr(cmd, '/'))
		return (cmd);
	else if (ft_strchr(cmd, '/') == 0 && check_if_in("PATH", env) == 0)
		return (clean_set_up(NULL, cmd));
	while (*env)
	{
		if (ft_strncmp(*env, "PATH=", 5) == 0)
			break ;
		env++;
	}
	(*env == NULL) && clean_exit(NULL, cmd);
	*env += 5;
	path = ft_split_empty(*env, ':');
	while (*path)
	{
		*path = clean_set_up(*path, cmd);
		if (access(*path, F_OK) == 0)
			break ;
		path++;
	}
	return (clean_exit(*path, cmd));
}

int	ft_wc(char *s, char c)
{
	int	counter;
	int	flag;

	flag = 1;
	counter = 0;
	while (*s)
	{
		while (*s == c)
		{
			s++;
			flag = 1;
		}
		if ((*s != c && flag == 1) && *s)
		{
			counter++;
			flag = 0;
		}
		if (*s)
			s++;
	}
	return (counter + 1);
}

int	is_true_cntl(char *str, char cntl)
{
	int		i;
	char	c;

	c = 0;
	i = 0;
	if (str[0] == cntl)
		c = str[0];
	else
		return (0);
	while (str[i])
	{
		if (str[i] != c)
			return (0);
		i++;
	}
	return (1);
}
