/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ted-dafi <ted-dafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 13:55:16 by ted-dafi          #+#    #+#             */
/*   Updated: 2022/08/13 10:12:52 by ted-dafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ted_dafi.h"

char	*make_history(char *cmd)
{
	static char	*history;

	if (cmd)
	{
		add_history(cmd);
		history = re_join(history, \
			re_join(ft_strdup(cmd), ft_strdup("\n")));
	}
	return (history);
}

int	put_history(void)
{
	int		fd;
	char	*s;
	char	*history;

	s = ft_strdup(getenv("HOME"));
	s = re_join(s, ft_strdup("/.minishell_history"));
	fd = open(s, O_WRONLY | O_TRUNC | O_CREAT, 0600);
	free(s);
	if (fd == -1)
		return (write(2, "minishell: failed to save history.\n", 35));
	history = make_history(NULL);
	if (history)
		write(fd, history, ft_strlen(history));
	close(fd);
	return (1);
}

int	load_history(void)
{
	int		fd;
	char	*str;
	char	*s;

	s = ft_strdup(getenv("HOME"));
	s = re_join(s, ft_strdup("/.minishell_history"));
	fd = open(s, O_RDONLY, 0600);
	free(s);
	if (fd == -1)
		return (write(2,
				"minishell: failed to load history, please relaunch\n", 51));
	str = get_next_line(fd);
	while (str)
	{
		make_history(str);
		free(str);
		str = get_next_line(fd);
	}
	close(fd);
	return (0);
}
