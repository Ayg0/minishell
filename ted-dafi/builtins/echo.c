/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msouiyeh <msouiyeh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 11:36:40 by ted-dafi          #+#    #+#             */
/*   Updated: 2022/07/02 17:59:04 by msouiyeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ted_dafi.h"

void	echo(t_pokets *poket)
{
	int	new_line;
	int	i;

	new_line = 1;
	i = 1;
	while (poket->av[i])
	{
		if (i > 1 + !new_line)
			write(1, " ", 1);
		if (i == 1 && ft_strcmp(poket->av[i], "-n") == 0)
			new_line = 0;
		else
			write(1, poket->av[i], ft_strlen(poket->av[i]));
		i++;
	}
	new_line && write(1, "\n", 1);
}
