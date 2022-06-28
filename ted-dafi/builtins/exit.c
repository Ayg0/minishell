/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ted-dafi <ted-dafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 11:36:11 by ted-dafi          #+#    #+#             */
/*   Updated: 2022/06/28 11:46:33 by ted-dafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ted_dafi.h"

int	ft_atoi(const char *str)
{
	int				i;
	int				sign;
	unsigned long	num;

	i = 0;
	sign = 1;
	num = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
	{
		i++;
	}
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		num *= 10;
		num += str[i] - '0';
		i++;
	}
	return (num, sign);
}

int	main(int ac, char **av)
{
	printf("exit\n");
	if (ac > 1)
		exit((unsigned char) ft_atoi(av[1]));
	exit(0);
}
