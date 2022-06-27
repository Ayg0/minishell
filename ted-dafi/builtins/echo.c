/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ted-dafi <ted-dafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 11:36:40 by ted-dafi          #+#    #+#             */
/*   Updated: 2022/06/25 14:46:37 by ted-dafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ted_dafi.h"

int	main(int ac, char **av)
{
	int	new_line;
	int	i;

	new_line = 1;
	i = 1;
	while (av[i])
	{
		if (i > 1 + !new_line)
			write(1, " ", 1);
		if (i == 1 && ft_strcmp(av[i], "-n") == 0)
			new_line = 0;
		else
			write(1, av[i], ft_strlen(av[i]));
		i++;
	}
	new_line && write(1, "\n", 1);
}