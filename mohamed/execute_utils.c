/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msouiyeh <msouiyeh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 08:35:10 by msouiyeh          #+#    #+#             */
/*   Updated: 2022/06/30 08:35:38 by msouiyeh         ###   ########.fr       */
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
			write (2, "pipex: ", 8);
			write (2, cmd, ft_strlen(cmd));
			write (2, ": permission denied\n", 20);
			exit(126);
		}
	}
	else
	{
		write (2, "pipex: ", 8);
		write (2, cmd, ft_strlen(cmd));
		write (2, ": command not found\n", 20);
		exit(127);
	}
	return (NULL);
}

char	*clean_set_up(char *path, char *cmd)
{
	char	*tmp;
	char	*final;

	final = NULL;
	tmp = ft_strjoin("/", cmd);
	final = ft_strjoin(path, tmp);
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
