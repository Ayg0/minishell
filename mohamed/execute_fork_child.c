/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_fork_child.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ted-dafi <ted-dafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 08:42:17 by msouiyeh          #+#    #+#             */
/*   Updated: 2022/07/01 17:37:24 by ted-dafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mohamed.h"

int	check_if_in(char *srch_for, char **srch_in)
{
	int i;

	i = 0;
	if (srch_in)
	{
		while (srch_in[i])
		{
			if (env_scout(srch_in[i], srch_for) != -1)
				return (1);
			i++;
		}
	}
	return (0);
}

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
	}
	else if (poket->outfile_fd == 2)
		ft_dup(poket->pip[WRITE_END], 1);
	if (poket->av == NULL)
		exit (0);
	if (is_built_in(poket->av) != -1)
	{
		launch_built_in(is_built_in(poket->av), poket);
		exit (get_global_error());
	}
	poket->path = ready_path(*(poket->env), poket->av[0]);
	if (execve(poket->path, poket->av, *(poket->env)) == -1)
	{
		write (2, "minishell: ", 11);
		write (2, poket->av[0], ft_strlen(poket->av[0]));
		if (errno == ENOENT || check_if_in("PATH", *(poket->env)) == 0)
			write (2, ": no such a file or directory\n", 31);
		else if (check_if_in("PATH", *(poket->env)))
			write (2, ": command not found\n", 21);
		exit (127);
	}
}

void	fork_it_helper(t_pokets *itire)
{
	if (itire->prev)
		close(itire->prev->pip[READ_END]);
	else if (itire->infile_fd != 0)
		close(itire->infile_fd);
	if (itire->next)
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