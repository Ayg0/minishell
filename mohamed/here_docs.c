/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_docs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msouiyeh <msouiyeh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 15:24:44 by msouiyeh          #+#    #+#             */
/*   Updated: 2022/07/31 14:29:29 by msouiyeh         ###   ########.fr       */
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
			return (final);
		str = here_doc_join(str, "\n", 0);
		if (flag != -1 && compare(str, limiter, 0))
			str = check_and_expand(str, envp);
		if (compare(str, limiter, 0))
			final = ult_strjoin(final, str, 1);
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
	close (fd);
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

	pid = fork();
	if (pid == 0)
		launch_helper(data, envp);
	else
		here_doc_parent_wait(pid);
	if (get_global_error() == 0)
		change_in_parrent(data);
}
