/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_fork_child.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msouiyeh <msouiyeh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 08:42:17 by msouiyeh          #+#    #+#             */
/*   Updated: 2022/07/22 00:49:21 by msouiyeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mohamed.h"

int	check_if_in(char *srch_for, char **srch_in)
{
	int	i;

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

void	prepare_in_out(t_pokets *poket)
{
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
}

void	go_child(t_pokets *poket)
{
	signal(SIGQUIT, SIG_DFL);
	prepare_in_out(poket);
	if (poket->av == NULL)
		exit (0);
	set_exit_code(0);
	if (is_built_in(poket->av) != -1)
	{
		launch_built_in(is_built_in(poket->av), poket);
		exit (get_global_error());
	}
	poket->path = ready_path(*(poket->env), poket->av[0]);
	if (execve(poket->path, poket->av, *(poket->env)) == -1)
	{
		if (errno == ENOENT || check_if_in("PATH", *(poket->env)) == 0)
			ft_putstr_fd (ult_strjoin(ult_strjoin("minishell: "\
			, poket->av[0], 0), ": no such a file or directory\n", 1), 2);
		else if (check_if_in("PATH", *(poket->env)))
			ft_putstr_fd (ult_strjoin(ult_strjoin("minishell: "\
			, poket->av[0], 0), ": command not found\n", 1), 2);
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
