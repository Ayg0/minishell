/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_valid.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ted-dafi <ted-dafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 00:59:35 by ted-dafi          #+#    #+#             */
/*   Updated: 2022/07/22 08:45:15 by ted-dafi         ###   ########.fr       */
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

int	switch_values(int j, int *b, char c, int flag)
{
	if (c == '=')
		*b = flag;
	return (!(j == 0));
}

int	all_valid(char	**av, int flag, char *built_err)
{
	int	i;
	int	res;

	i = 0;
	res = 0;
	while (av[i])
	{
		res += iterate_check(av[i], flag, built_err);
		i++;
	}
	return ((res > 0));
}
