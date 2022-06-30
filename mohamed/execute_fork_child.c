/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_fork_child.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msouiyeh <msouiyeh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 08:42:17 by msouiyeh          #+#    #+#             */
/*   Updated: 2022/06/30 12:34:15 by msouiyeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mohamed.h"

void	go_child(t_pokets *poket)
{
	signal(SIGQUIT, SIG_DFL);
	close (poket->pip[READ_END]);
	if (poket->infile_fd > 2)
		ft_dup(poket->infile_fd, 0);
	else if (poket->infile_fd == 2)
		ft_dup(poket->prev->pip[READ_END], 0);
	if (poket->outfile_fd > 2)
	{
		ft_dup(poket->outfile_fd, 1);
		close (poket->pip[WRITE_END]);
		// if (poket->next != NULL)
	}
	else if (poket->outfile_fd == 2)
		ft_dup(poket->pip[WRITE_END], 1);
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

void	fork_it_helper(t_pokets *itire)
{
	
	if (itire->infile_fd == 2)
		close(itire->prev->pip[READ_END]);
	else if (itire->infile_fd != 0)
		close(itire->infile_fd);
	if (itire->outfile_fd == 2)
		close (itire->pip[WRITE_END]);
	else if (itire->outfile_fd != 1)
		close (itire->outfile_fd);
}

void	fork_print_error(char *error_str)
{
	ft_putendl_fd(error_str, 2);
	set_exit_code(1);
	set_global_error(1);
}

void	fork_it(t_pokets *pokets)
{
	pid_t		pid;
	t_pokets	*itire;

	itire = pokets;
	while (itire)
	{
		if (pipe(itire->pip) == -1)
			return (fork_print_error("minishell: piping failed"));
		pid = fork();
		if (pid < 0)
			return (fork_print_error("minishell: fork failed"));
		else if (pid == 0)
			go_child(itire);
		fork_it_helper(itire);
		itire = itire->next;
	}
	pokets->last_pid = pid;
}
