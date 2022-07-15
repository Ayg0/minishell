/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ted-dafi <ted-dafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 12:12:35 by ted-dafi          #+#    #+#             */
/*   Updated: 2022/07/15 11:06:33 by ted-dafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ted_dafi.h"

void	env(t_pokets *poket)
{
	int		i;
	char	**envp;

	i = 0;
	envp = *(poket->env);
	while (envp && envp[i])
	{
		if (ft_strchr(envp[i], '='))
		{
			write(1, envp[i], ft_strlen(envp[i]));
			write(1, "\n", 1);
		}
		i++;
	}
	set_exit_code(0);
	set_global_error(0);
}
