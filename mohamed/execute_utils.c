/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ted-dafi <ted-dafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 08:35:10 by msouiyeh          #+#    #+#             */
/*   Updated: 2022/07/22 15:21:21 by ted-dafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mohamed.h"

void	ft_perror(char *str)
{
	perror(str);
	(errno);
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
			ft_putstr_fd(ult_strjoin(ult_strjoin("minishell: ", cmd, 0) \
			, ": permission denied\n", 0), 2);
			exit(126);
		}
	}
	else
	{
		ft_putstr_fd(ult_strjoin(ult_strjoin("minishell: ", cmd, 0) \
		, ": command not found\n", 0), 2);
		exit(127);
	}
	return (NULL);
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
	if (path)
		tmp = exec_join("/", cmd);
	else if (path == NULL)
		return (exec_join("./", cmd));
	final = exec_join(path, tmp);
	free(path);
	free(tmp);
	return (final);
}
