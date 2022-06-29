/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msouiyeh <msouiyeh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 23:12:34 by msouiyeh          #+#    #+#             */
/*   Updated: 2022/06/28 23:45:13 by msouiyeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mohamed.h"

void	ft_perror(char *str)
{
	perror(str);
	exit(errno);
}

void	ft_dup(int fd_one, int fd_two, int flag)
{
	if (flag && fd_one == -1)
		exit (EXIT_FAILURE);
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

void	go_child(t_pokets *poket)
{
	close (poket->pip[READ_END]);
	if (poket->next != NULL)
		close (poket->outfile_fd);
	if (poket->prev == NULL)
		ft_dup(poket->infile_fd, 0, 1);
	else
		ft_dup(poket->prev->pip[READ_END], 0, 0);
	if (poket->next == NULL)
		ft_dup(poket->outfile_fd, 1, 1);
	else
		ft_dup(poket->pip[WRITE_END], 1, 0);
	poket->path = ready_path(poket->env, poket->av[0]);
	if (execve(poket->path, poket->av, poket->env) == -1)
	{
		write (2, "pipex: ", 8);
		write (2, poket->av[0], ft_strlen(poket->av[0]));
		write (2, ": ", 2);
		ft_perror(NULL);
	}
}

void	fork_it(t_pokets *pokets)
{
	pid_t	pid;
	t_pokets	*itire;

	itire = pokets;
	while (itire)
	{
		if (itire->next != NULL)
			if (pipe(itire->pip) == -1)
				ft_perror("pipex: pip:");
		pid = fork();
		if (pid < 0)
			ft_perror("pipex");
		else if (pid == 0)
			go_child(itire);
		if (itire->prev == NULL)
			close(itire->infile_fd);
		else if (itire->prev != NULL)
			close(itire->prev->pip[READ_END]);
		if (itire->next == NULL)
			close (itire->outfile_fd);
		else if (itire->next != NULL)
			close (itire->pip[WRITE_END]);
		itire = itire->next;
	}
	pokets->last_pid = pid;
}

void	wait_for_the_kids(t_pokets *poket)
{
	int	info;
	int	child_errno;
	int	pid;

	child_errno = EXIT_SUCCESS;
	pid = 1;
	while (pid > 0)
	{
		pid = waitpid(-1, &info, 0);
		if (pid < 0)
		{
			if (errno == ECHILD)
				break ;
			perror("pipex: wait_for_the_kids:");
			exit(errno);
		}
		if (WIFEXITED(info) && pid == poket->last_pid)
			child_errno = WEXITSTATUS(info);
		else if (WIFSIGNALED(info) && pid == poket->last_pid)
			child_errno = 128 + WTERMSIG(info);
	}
	exit (child_errno);
}

void	open_redirects(t_pokets *pokets)
{
	while (pokets)
	{
		pokets = pokets->next;
	}
}

void	execute_pipline(t_pokets *pokets)
{
	open_redirects(pokets);
}