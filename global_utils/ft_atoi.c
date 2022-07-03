/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msouiyeh <msouiyeh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 17:05:39 by ted-dafi          #+#    #+#             */
/*   Updated: 2022/07/02 16:00:18 by msouiyeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "global_utils.h"
#include <stdio.h>

void	help(unsigned long num, int sign, int *flag)
{
	if ((num > 9223372036854775807 && sign == 1)
		|| (num > 9223372036854775808UL && sign == -1))
		*flag = -1;
}

int	ft_atoi(char *str, int *flag)
{
	int				i;
	int				sign;
	unsigned long	num;

	i = 0;
	sign = 1;
	num = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '+' || str[i] == '-')
		if (str[i++] == '-')
			sign *= -1;
	if (!(str[i] >= '0' && str[i] <= '9') && flag)
		*flag = -1;
	while (str[i] >= '0' && str[i] <= '9')
	{
		num *= 10;
		num += str[i] - '0';
		help(num, sign, flag);
		i++;
	}
	if (str[i] && flag)
		*flag = -1;
	return (num * sign);
}
