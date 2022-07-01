/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ted-dafi <ted-dafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 08:35:10 by msouiyeh          #+#    #+#             */
/*   Updated: 2022/07/01 17:38:15 by ted-dafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mohamed.h"

void	ft_perror(char *str)
{
	perror(str);
	exit(errno);
}

void	ft_dup(int fd_one, int fd_two)
{
	dup2(fd_one, fd_two);
	close (fd_one);
}

char	*clean_exit(char *path, char *cmd)
{
	if (path)
	{
		if (access(path, X_OK) == 0)
			return (path);
		else
		{
			write (2, "minishell: ", 11);
			write (2, cmd, ft_strlen(cmd));
			write (2, ": permission denied\n", 20);
			exit(126);
		}
	}
	else
	{
		//remove the one
		write (2, "minishell: ", 11);
		write (2, cmd, ft_strlen(cmd));
		write (2, ": command not found\n", 20);
		exit(127);
	}
	return (NULL);
}

char 	*exec_join(char *s1, char *s2)
{
	char	*final;

	if (s1 == NULL)
		return (NULL);
	if (s2 == NULL)
		return (NULL);
	final = ft_strjoin(s1, s2);
	return (final);
}

char	*clean_set_up(char *path, char *cmd)
{
	char	*tmp;
	char	*final;

	final = NULL;
	tmp = NULL;
	if (path)
		tmp = exec_join("/", cmd);
	else if (path == NULL)
		return (exec_join("./", cmd));
	final = exec_join(path, tmp);
	free(path);
	free(tmp);
	return (final);
}

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
	if (*env == NULL)
		return (clean_exit(NULL, cmd));
	*env += 5;
	path = ft_split(*env, ':');
	while (*path)
	{
		*path = clean_set_up(*path, cmd);
		if (access(*path, F_OK) == 0)
			break ;
		path++;
	}
	return (clean_exit(*path, cmd));
}
