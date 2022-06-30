/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_docs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msouiyeh <msouiyeh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 15:24:44 by msouiyeh          #+#    #+#             */
/*   Updated: 2022/06/30 06:54:55 by msouiyeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	compare(char *str, char *limiter, int flag)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (1);
	while (str[i] == limiter[i] || !(limiter[i]))
	{
		if (!(limiter[i]) && str[i] == '\n')
		{
			if (flag)
				free(str);
			return (0);
		}
		i++;
	}
	if (flag)
		free(str);
	return (1);
}

char	*dynamic_read(char *limiter, int flag, char **envp)
{
	char	*str;
	char	*final;
	int		size;

	if (flag == -1)
		limiter = remove_limiter_q(limiter);
	size = ft_strlen(limiter);
	str = NULL;
	final = ft_strdup("");
	while (compare(str, limiter, 1))
	{
		write (1, "> ", 2);
		str = get_next_line(0);
		if (str == NULL)
			return (final);
		if (flag != -1 && compare(str, limiter, 0))
			str = check_and_expand(str, envp);
		if (compare(str, limiter, 0))
			final = ft_strjoin_all(&final, str);
	}
	if (flag == -1)
		free(limiter);
	return (final);
}

void	here_doc(int fd, char *limiter, char **envp)
{
	char	*final;
	int		i;

	i = 0;
	while (limiter[i])
	{
		if (limiter[i] == '\'' || limiter[i] == '\"')
		{
			i = -1;
			break ;
		}
		i++;
	}
	final = dynamic_read(limiter, i, envp);
	write(fd, final, ft_strlen(final));
	if (close (fd) == -1)
		printf("error msg in heredoc to be changed\n");
	free(final);
}

void	change_here_doc(t_tokens *itire, char *path)
{
	free(itire->next->token);
	itire->next->token = ft_strdup(path);
	free(itire->next->meta_data);
	itire->next->meta_data = get_meta(itire->next->token);
}

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
				printf("here_doc tmp file creation faild\n");
			here_doc (fd, itire->next->token, envp);
			change_here_doc(itire, path);
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
		ft_putstr_fd("error max here_doc is exeeded\n", 2);
		exit(1);
	}
	helper_loop(itire, path, envp);
	free(path);
	exit(0);
}

void	change_in_parrent(t_data *data)
{
	char		*path;
	t_tokens	*itire;
	int			i;

	path = ft_strdup("/tmp/here_doc..");
	itire = data->list;
	i = 0;
	while (itire)
	{
		if (ft_strchr("r", *(itire->meta_data)) && \
			ft_strlen(itire->meta_data) == 2)
		{
			path[13] = (i / 10) + '0';
			path[14] = (i % 10) + '0';
			change_here_doc(itire, path);
			i++;
		}
		itire = itire->next;
	}
	free(path);
}

void	launch_here_docs(t_data *data, char **envp)
{
	int	pid;
	int	info;

	pid = fork();
	if (pid == 0)
		launch_helper(data, envp);
	else
	{
		signal(SIGINT, SIG_IGN);
		pid = waitpid(pid, &info, 0);
		if (pid < 0)
		{
			ft_putendl_fd("minishell : waitpid faild", 2);
			set_global_error(1);
			set_exit_code(1);
		}
		if (WIFEXITED(info))
		{
			set_global_error(WEXITSTATUS(info));
			if (get_global_error() != 0)
				set_exit_code(get_global_error());
		}
		if (WIFSIGNALED(info))
		{
			write (1, "\n", 1);
			set_global_error(1);
			set_exit_code(1);
		}
		signal(SIGINT, handle_sigint);
	}
	if (get_global_error() == 0)
		change_in_parrent(data);
}
