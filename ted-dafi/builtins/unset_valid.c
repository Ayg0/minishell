/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_valid.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ted-dafi <ted-dafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 00:59:35 by ted-dafi          #+#    #+#             */
/*   Updated: 2022/07/01 15:24:43 by ted-dafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ted_dafi.h"

int	give_unvalid_error(char *av, char *built_err)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(built_err, 2);
	ft_putstr_fd(": `", 2);
	ft_putstr_fd(av, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	set_global_error(1);
	set_exit_code(1);
	return (1);
}

int	lower_cond(char c, char c2, int flag)
{
	return ((c != '=' * flag) && !(c == '+' && c2 == '='));
}

int	upper_cond(char c, char *av, char *built_err)
{
	return ((c == '\0' || c == '+' || c == '=')
		&& give_unvalid_error(av, built_err));
}

int	all_valid(char	**av, int flag, char *built_err)
{
	int	i;
	int	j;
	int	num_flag;
	int	b;

	i = 0;
	b = 0;
	while (av[i])
	{
		j = 0;
		if (upper_cond(av[i][j], av[i], built_err))
			return (0);
		while (av[i][j])
		{
			num_flag = 1;
			if (j == 0)
				num_flag = 0;
			if (av[i][j] == '=')
				b = 1 * flag;
			if ((!check_validation(av[i][j], 0, num_flag)
				&& lower_cond(av[i][j], av[i][j + 1], flag)) && !b)
				return (give_unvalid_error(av[i], built_err));
			j++;
		}
		i++;
		if (flag)
			break ;
	}
	return (1);
}
