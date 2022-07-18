/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ted-dafi <ted-dafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 11:36:11 by ted-dafi          #+#    #+#             */
/*   Updated: 2022/07/18 10:03:03 by ted-dafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ted_dafi.h"

void	ft_exit(t_pokets *poket)
{
	int				flag;
	unsigned char	num;

	write(1, "exit\n", 5);
	if (!poket->av[1])
		exit(0);
	else if (poket->av[2])
	{
		set_exit_code(ft_putstr_fd("\033[0;34mminishell\033[0;37m: exit: too many arguments\n", 2));
		return (set_global_error(1));
	}
	flag = 0;
	num = (unsigned char) ft_atoi(poket->av[1], &flag);
	if (!flag)
		exit(num);
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(poket->av[1], 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	exit(255);
}
