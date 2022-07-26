/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msouiyeh <msouiyeh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 11:36:40 by ted-dafi          #+#    #+#             */
/*   Updated: 2022/07/27 00:08:13 by msouiyeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ted_dafi.h"

int	arg_new_line(char	*av)
{
	int	i;

	i = 0;
	while (av[i] || i == 0)
	{
		if ((i == 0 && av[i] != '-') || (i > 0 && av[i] != 'n'))
			return (0);
		i++;
	}
	return (1);
}

void	echo(t_pokets *poket)
{
	int	new_line;
	int	i;
	int	first;

	new_line = 1;
	first = 0;
	i = 1;
	while (poket->av[i])
	{
		if (!first && arg_new_line(poket->av[i]))
			new_line = 0;
		else
		{
			if (!first)
				first = 1;
			else
				write(1, " ", 1);
			write(1, poket->av[i], ft_strlen(poket->av[i]));
		}
		i++;
	}
	new_line && write(1, "\n", 1);
	set_exit_code(0);
	set_global_error(0);
}
