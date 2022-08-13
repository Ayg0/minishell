/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ted-dafi <ted-dafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 10:16:00 by ted-dafi          #+#    #+#             */
/*   Updated: 2022/08/13 12:35:57 by ted-dafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ted_dafi.h"

int	cd_error(t_pokets *poket, int err)
{
	char	*tmp;
	char	*tmp2;

	tmp2 = NULL;
	if (err == -1)
	{
		if (poket->av[1])
			tmp2 = ft_strdup(poket->av[1]);
		else
			tmp2 = get_exp(ft_strdup("HOME"), 'q', *poket->env);
		tmp = re_join(ft_strdup("minishell: cd: "), tmp2);
		perror(tmp);
		free(tmp);
	}
	else
		ft_putstr_fd(ft_strdup("minishell: cd: HOME not set\n"), 2);
	set_exit_code(1);
	set_global_error(1);
	return (1);
}
