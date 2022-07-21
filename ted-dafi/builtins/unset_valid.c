/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_valid.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msouiyeh <msouiyeh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 00:59:35 by ted-dafi          #+#    #+#             */
/*   Updated: 2022/07/21 21:37:13 by msouiyeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ted_dafi.h"

int	give_unvalid_error(char *av, char *built_err)
{
	char	*tmp;

	tmp = re_join(ft_strdup("minishell: "), ft_strdup(built_err));
	tmp = re_join(tmp, ft_strdup(": `"));
	tmp = re_join(tmp, ft_strdup(av));
	tmp = re_join(tmp, ft_strdup("': not a valid identifier\n"));
	ft_putstr_fd(tmp, 2);
	set_global_error(2);
	set_exit_code(2);
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

int	switch_values(int j, int *b, char c, int flag)
{
	if (c == '=')
		*b = flag;
	return (!(j == 0));
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
			num_flag = switch_values(j, &b, av[i][j], flag);
			if ((!check_validation(av[i][j], 0, num_flag)
				&& lower_cond(av[i][j], av[i][j + 1], flag)) && !b)
				return (give_unvalid_error(av[i], built_err));
			j++;
		}
		i++;
		if (!flag)
			break ;
	}
	return (1);
}
