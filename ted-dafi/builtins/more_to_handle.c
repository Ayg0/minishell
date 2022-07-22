/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_to_handle.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ted-dafi <ted-dafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 08:43:18 by ted-dafi          #+#    #+#             */
/*   Updated: 2022/07/22 08:44:23 by ted-dafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ted_dafi.h"

int	iterate_check(char *av, int flag, char *built_err)
{
	int	num_flag;
	int	b;
	int	j;

	b = 0;
	j = 0;
	while (av[j] || !j)
	{
		if (j == 0 && upper_cond(av[j], av, built_err))
			return (1);
		num_flag = switch_values(j, &b, av[j], flag);
		if ((!check_validation(av[j], 0, num_flag)
				&& lower_cond(av[j], av[j + 1], flag)) && !b)
		{
			give_unvalid_error(av, built_err);
			return (1);
		}
		j++;
	}
	return (0);
}
