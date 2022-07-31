/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_redicts.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msouiyeh <msouiyeh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 08:37:57 by msouiyeh          #+#    #+#             */
/*   Updated: 2022/07/31 15:46:58 by msouiyeh         ###   ########.fr       */
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
			ft_putstr_fd(ult_strjoin("minishell: ", \
			ult_strjoin(tmp->file_name, ": No such file or directory\n", 0), 2) \
				, 2);
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
			ft_putstr_fd(ult_strjoin("minishell: faild to open "\
			, ult_strjoin(tmp->file_name, "\n", 0), 2), 2);
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
		if (pokets->index != -1 && open_write(pokets) == 1)
			return ;
		if (pokets->index != -1 && open_read(pokets) == 1)
			return ;
		pokets = pokets->next;
	}
}

void	unlink_helper(int unlnk, char *path)
{
	unlnk = EBUSY;
	while (unlnk == EBUSY)
	{
		unlnk = unlink(path);
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
	char	*path;
	int		i;

	i = 0;
	path = ft_strdup("/tmp/here_doc..");
	(void)pokets;
	while (i < 16)
	{
		path[13] = (i / 10) + '0';
		path[14] = (i % 10) + '0';
		if (access(path, F_OK) != -1)
			unlink_helper(0, path);
		else
			break ;
		i++;
	}
	free (path);
}
