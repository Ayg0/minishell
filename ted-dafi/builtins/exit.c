/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ted-dafi <ted-dafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 11:36:11 by ted-dafi          #+#    #+#             */
/*   Updated: 2022/07/22 15:47:28 by ted-dafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ted_dafi.h"

int	my_exit(unsigned char num, t_pokets *poket)
{
	if (poket && !(poket->prev) && !(poket->next))
		put_history();
	exit(num);
}

void	ft_exit(t_pokets *poket)
{
	int				flag;
	unsigned char	num;
	char			*tmp;

	!(poket->prev) && write(1, "exit\n", 5);
	if (!poket->av[1])
		my_exit(0, poket);
	flag = 0;
	num = (unsigned char) ft_atoi(poket->av[1], &flag);
	if (!flag && !poket->av[2])
		my_exit(num, poket);
	else if (flag)
	{
		tmp = re_join(ft_strdup("minishell: exit: "), ft_strdup(poket->av[1]));
		tmp = re_join(tmp, ft_strdup(": numeric argument required\n"));
		ft_putstr_fd(tmp, 2);
		my_exit(255, poket);
	}
	set_exit_code(ft_putstr_fd(\
	ft_strdup("minishell : exit: too many arguments\n"), 2));
	return (set_global_error(1));
}
