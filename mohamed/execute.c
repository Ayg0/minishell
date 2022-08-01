/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msouiyeh <msouiyeh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 23:12:34 by msouiyeh          #+#    #+#             */
/*   Updated: 2022/08/01 00:13:07 by msouiyeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mohamed.h"

int	wait_help(int info, int pid, t_pokets *poket)
{
	int	child_errno;

	child_errno = EXIT_SUCCESS;
	if (WIFEXITED(info) && pid == poket->last_pid)
	{	
		child_errno = WEXITSTATUS(info);
		set_exit_code(child_errno);
	}
	else if (WIFSIGNALED(info) && pid == poket->last_pid)
	{
		child_errno = 128 + WTERMSIG(info);
		set_exit_code(child_errno);
		if (child_errno == 131)
			write(1, "Quit: 3\n", 8);
	}
	return (child_errno);
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
			perror("minishell");
			set_exit_code(errno);
		}
		child_errno = wait_help(info, pid, poket);
	}
	set_termios_attr();
	signal(SIGINT, handle_sigint);
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
	built_ins[7] = "history";
	built_ins[8] = NULL;
}

int	is_built_in(char **cmd)
{
	char	*built_ins[9];
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
	int	out;

	out = 1;
	open_redirects(pokets);
	if (is_built_in(pokets->av) != -1 && !(pokets->next) && !(pokets->prev))
	{
		if (pokets->index == -1)
			return (set_exit_code(1));
		resettermios_attr();
		if (pokets->outfile_fd != 1)
		{	
			out = dup(1);
			ft_dup(pokets->outfile_fd, 1);
		}
		launch_built_in(is_built_in(pokets->av), pokets);
		if (pokets->outfile_fd != 1)
			ft_dup(out, 1);
		set_termios_attr();
		return ;
	}
	fork_it(pokets);
	wait_for_the_kids(pokets);
	unlink_here_docs(pokets);
}
