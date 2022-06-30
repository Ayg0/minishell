/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_redicts.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msouiyeh <msouiyeh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 08:37:57 by msouiyeh          #+#    #+#             */
/*   Updated: 2022/06/30 11:56:05 by msouiyeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mohamed.h"

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
			set_global_error(1);
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
			set_global_error(1);
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

void	unlink_helper(int unlnk, t_redirect *tmp)
{
	unlnk = EBUSY;
	while (unlnk == EBUSY)
	{
		unlnk = unlink(tmp->file_name);
		if (unlnk != EBUSY && unlnk != 0)
		{
			perror("minishell :");
			set_exit_code(errno);
			set_global_error(errno);
		}
	}
}

void	unlink_here_docs(t_pokets *pokets)
{
	t_redirect	*tmp;

	while (pokets)
	{
		tmp = pokets->redirects->read;
		while (tmp)
		{
			if (tmp->type == 'h')
				unlink_helper(0, tmp);
			tmp = tmp->next;
		}
		pokets = pokets->next;
	}
}
