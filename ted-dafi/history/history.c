/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msouiyeh <msouiyeh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 13:55:16 by ted-dafi          #+#    #+#             */
/*   Updated: 2022/08/10 22:00:48 by msouiyeh         ###   ########.fr       */
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
	char	*history;

	fd = open(".minishell_history", O_RDWR | O_TRUNC | O_CREAT, 0600);
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

	fd = open(".minishell_history", O_RDONLY, 0600);
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
