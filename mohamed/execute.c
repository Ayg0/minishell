/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msouiyeh <msouiyeh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 23:12:34 by msouiyeh          #+#    #+#             */
/*   Updated: 2022/06/30 05:32:46 by msouiyeh         ###   ########.fr       */
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

void	go_child(t_pokets *poket)
{
	// signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (poket->next != NULL)
		close (poket->pip[READ_END]);
	if (poket->infile_fd > 2)
	{	
		ft_dup(poket->infile_fd, 0);	
	}
	else if (poket->infile_fd == 2)
	{
		ft_dup(poket->prev->pip[READ_END], 0);
	}
	if (poket->outfile_fd > 2)
	{	
		ft_dup(poket->outfile_fd, 1);
	}
	else if (poket->outfile_fd == 2)
	{
		ft_dup(poket->pip[WRITE_END], 1);
	}
	poket->path = ready_path(*poket->env, poket->av[0]);
	if (execve(poket->path, poket->av, *poket->env) == -1)
	{
		write (2, "pipex: ", 8);
		write (2, poket->av[0], ft_strlen(poket->av[0]));
		write (2, ": ", 2);
		ft_perror(NULL);
		exit (errno);
	}
}

void	fork_it(t_pokets *pokets)
{
	pid_t		pid;
	t_pokets	*itire;

	itire = pokets;
	while (itire)
	{
		if (itire->next != NULL)
			if (pipe(itire->pip) == -1)
			{
				ft_putendl_fd("minishell: piping failed", 2);
				set_exit_code(1);
				return ;
			}
		pid = fork();
		if (pid < 0)
			ft_perror("pipex");
		else if (pid == 0)
			go_child(itire);
		if (itire->infile_fd == 2)
			close(itire->prev->pip[READ_END]);
		else if (itire->infile_fd != 0)
			close(itire->infile_fd);
		if (itire->outfile_fd == 2)
			close (itire->pip[WRITE_END]);
		else if (itire->outfile_fd != 1)
			close (itire->outfile_fd);
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
	signal(SIGINT, SIG_IGN);
	while (pid > 0)
	{
		pid = waitpid(-1, &info, 0);
		if (pid < 0)
		{
			if (errno == ECHILD)
				break ;
			perror("minishell: waiting for shiled process failed:");
			set_exit_code(errno);
		}
		if (WIFEXITED(info) && pid == poket->last_pid)
			child_errno = WEXITSTATUS(info);
		else if (WIFSIGNALED(info) && pid == poket->last_pid)
			child_errno = 128 + WTERMSIG(info);
	}
	set_exit_code(child_errno);
	signal(SIGINT, handle_sigint);
}

int	open_read(t_pokets *pokets)
{
	t_redirect	*tmp;

	tmp = pokets->redirects->read;
	pokets->infile_fd = 2;
	if (pokets->prev == NULL)
		pokets->infile_fd = 0;
	while (tmp)
	{
		pokets->infile_fd = open(tmp->file_name, tmp->code, 0666);
		if (pokets->infile_fd == -1)
		{
			ft_putstr_fd("minishell: faild to open ", 2);
			ft_putendl_fd(tmp->file_name, 2);
			set_exit_code(1);
			return (1);
		}
		if (tmp->next)
			close (pokets->infile_fd);
		tmp = tmp->next;
	}
	return (0);
}

int	open_write(t_pokets *pokets)
{
	t_redirect	*tmp;

	tmp = pokets->redirects->write;
	pokets->outfile_fd = 2;
	if (pokets->next == NULL)
		pokets->outfile_fd = 1;
	while (tmp)
	{
		pokets->outfile_fd = open(tmp->file_name, tmp->code, 0666);
		if (pokets->outfile_fd == -1)
		{
			ft_putstr_fd("minishell: faild to open ", 2);
			ft_putendl_fd(tmp->file_name, 2);
			set_exit_code(1);
			return (1);
		}
		if (tmp->next)
			close (pokets->outfile_fd);
		tmp = tmp->next;
	}
	return (0);
}

void	open_redirects(t_pokets *pokets)
{
	while (pokets)
	{
		if (open_read(pokets) == 1)
			return ;
		if (open_write(pokets) == 1)
			return ;
		pokets = pokets->next;
	}
}

void	unlink_here_docs(t_pokets *pokets)
{
	t_redirect	*tmp;
	int			unlnk;

	while (pokets)
	{
		tmp = pokets->redirects->read;
		while (tmp)
		{
			if (tmp->type == 'h')
			{
				unlnk = EBUSY;
				while (unlnk == EBUSY)
				{
					unlnk = unlink(tmp->file_name);
					if (unlnk != EBUSY && unlnk != 0)
					{
						perror("minishell :");
						set_exit_code(errno);
					}
				}
			}
			tmp = tmp->next;
		}
		pokets = pokets->next;
	}
}

void	set_built_ins(char **built_ins)
{
	built_ins[0] = "echo";
	built_ins[1] = "cd";
	built_ins[2] = "pwd";
	built_ins[3] = "export";
	built_ins[4] = "unset";
	built_ins[5] = "env";
	built_ins[6] = "exit";
	built_ins[7] = NULL;
}

int	is_built_in(char **cmd)
{
	char	*built_ins[8];
	int		i;

	i = 0;
	set_built_ins(built_ins);
	if (!cmd)
		return (-1);
	while (built_ins[i])
	{
		if (ft_strcmp(cmd[0], built_ins[i]) == 0)
			return (i);
		i++;
	}
	return (-1);
}

void	execute_pipline(t_pokets *pokets)
{
	open_redirects(pokets);
	if (get_exit_code() != 0)
		return ;
	// if (is_built_in(pokets->av) != -1 && !pokets->next && !pokets->prev)
	// {
	// 	//launch built in in parrant
	// 	;
	// }
	// else
	// {
		fork_it(pokets);
	// }
	wait_for_the_kids(pokets);
	unlink_here_docs(pokets);
}
