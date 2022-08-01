/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_fork.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msouiyeh <msouiyeh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 08:46:27 by msouiyeh          #+#    #+#             */
/*   Updated: 2022/07/31 13:49:44 by msouiyeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mohamed.h"

void	helper_loop(t_tokens *itire, char *path, char **envp)
{
	int	i;
	int	fd;

	i = 0;
	while (itire)
	{
		if (ft_strchr("r", *(itire->meta_data)) && \
			ft_strlen(itire->meta_data) == 2)
		{
			path[13] = (i / 10) + '0';
			path[14] = (i % 10) + '0';
			fd = open(path, O_CREAT | O_WRONLY | O_TRUNC, 0666);
			if (fd == -1)
			{
				ft_putstr_fd("minishell: here_doc tmp file creation faild\n", \
				2);
				exit (1);
			}
			here_doc (fd, itire->next->token, envp);
			i++;
		}
		itire = itire->next;
	}
}

int	launch_helper(t_data *data, char **envp)
{
	t_tokens	*itire;
	char		*path;

	signal(SIGINT, SIG_DFL);
	path = ft_strdup("/tmp/here_doc..");
	itire = data->list;
	if (check_max_here_doc(itire))
	{
		ft_putstr_fd("minishell: maximum here-document count exceeded\n", 2);
		exit(128);
	}
	helper_loop(itire, path, envp);
	free(path);
	exit(0);
}

void	change_in_parrent(t_data *data)
{
	char		*path;
	t_tokens	*itire;
	int			index;
	int			i;

	path = ft_strdup("/tmp/here_doc..");
	itire = data->list;
	i = 0;
	index = 0;
	while (itire)
	{
		if (ft_strchr("r", *(itire->meta_data)) && \
			ft_strlen(itire->meta_data) == 2)
		{
			path[13] = (i / 10) + '0';
			path[14] = (i++ % 10) + '0';
			change_here_doc(itire, path);
		}
		if (*(itire->meta_data) == 'p')
			index++;
		else
			itire->index = index;
		itire = itire->next;
	}
	free(path);
}

void	here_doc_parent_wait(int pid)
{
	int	info;

	signal(SIGINT, SIG_IGN);
	pid = waitpid(pid, &info, 0);
	if (pid < 0)
		fork_print_error("minishell : waitpid faild");
	if (WIFEXITED(info))
	{
		set_global_error(WEXITSTATUS(info));
		if (get_global_error() != 0)
		{
			if (get_global_error() == 128)
				exit (2);
			set_exit_code(get_global_error());
		}
	}
	if (WIFSIGNALED(info))
		fork_print_error("");
	signal(SIGINT, handle_sigint);
}
