/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msouiyeh <msouiyeh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 08:35:10 by msouiyeh          #+#    #+#             */
/*   Updated: 2022/08/13 12:29:52 by msouiyeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mohamed.h"

void	ft_dup(int fd_one, int fd_two)
{
	dup2(fd_one, fd_two);
	close (fd_one);
}

void	dir_check(char *cmd)
{
	struct stat	f_stat;

	stat(cmd, &f_stat);
	if (S_ISDIR(f_stat.st_mode))
	{
		ft_putstr_fd(ult_strjoin(ult_strjoin("minishell: ", cmd, 0) \
		, ": is a directory\n", 0), 2);
		exit (126);
	}
}

char	*clean_exit(char *path, char *cmd)
{
	if (path)
	{
		dir_check(cmd);
		if (access(path, X_OK) == 0)
			return (path);
		else if (access(path, F_OK) == 0)
			ft_putstr_fd(ult_strjoin(ult_strjoin("minishell: ", cmd, 0) \
			, ": permission denied\n", 0), 2);
		else
		{	
			ft_putstr_fd(ult_strjoin(ult_strjoin("minishell: ", cmd, 0) \
			, ": No such file or directory\n", 0), 2);
			exit (127);
		}
		exit(126);
	}
	else
	{
		ft_putstr_fd(ult_strjoin(ult_strjoin("minishell: ", cmd, 0) \
		, ": command not found\n", 0), 2);
		exit(127);
	}
}

char	*exec_join(char *s1, char *s2)
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
	if (!*cmd)
		clean_exit(NULL, cmd);
	if (path && *path == '\0')
		return (cmd);
	if (path)
		tmp = exec_join("/", cmd);
	else if (path == NULL)
		return (clean_exit(cmd, cmd));
	final = exec_join(path, tmp);
	free(path);
	free(tmp);
	return (final);
}
