/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_docs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ted-dafi <ted-dafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 15:24:44 by msouiyeh          #+#    #+#             */
/*   Updated: 2022/07/01 17:20:11 by ted-dafi         ###   ########.fr       */
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
		if (!(limiter[i]) && str[i] == '\0')
		{
			if (flag)
				free(str);
			return (0);
		}
		if (!(limiter[i]))
			break ; 
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
		str = readline("> ");
		if (str == NULL)
			return (NULL);
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
	if (final == NULL)
		return ;
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
	if (get_global_error() == 0)
		change_in_parrent(data);
}
