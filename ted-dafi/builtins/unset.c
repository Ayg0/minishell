/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ted-dafi <ted-dafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 18:28:23 by ted-dafi          #+#    #+#             */
/*   Updated: 2022/08/06 09:12:00 by ted-dafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ted_dafi.h"

int	check_if_equal(char	*srch_for, char	**srch_in)
{
	int	i;

	i = 0;
	while (srch_in[i])
	{
		if (!ft_strcmp(srch_in[i], srch_for) && ft_strcmp(srch_in[i], "_"))
		{
			free(srch_for);
			return (1);
		}
		i++;
	}
	free(srch_for);
	return (0);
}

int	search_for_them(char **envp, char **av)
{
	char	*equal_sign;
	int		i;
	int		total;

	i = 0;
	total = 0;
	while (envp[i])
	{
		equal_sign = ft_strchr(envp[i], '=');
		if (equal_sign)
			total -= check_if_equal(ft_substr(envp[i],
						0, equal_sign - envp[i]), av);
		i++;
	}
	total += i;
	return (total);
}

void	cpy_what_not(char **envpd, char **last_env, char **av)
{
	int		i;
	int		j;
	char	*equal_sign;

	i = 0;
	j = 0;
	while (last_env[i])
	{	
		equal_sign = ft_strchr(last_env[i], '=');
		if (equal_sign && check_if_equal(ft_substr(last_env[i],
					0, equal_sign - last_env[i]), av))
		{
			i++;
			continue ;
		}
		envpd[j++] = ft_strdup(last_env[i++]);
	}
}

void	unset(t_pokets *poket)
{
	int		i;
	int		res;
	char	**envpd;

	if (!poket->av[1])
		return ;
	res = all_valid(poket->av + 1, 0, "unset");
	i = search_for_them(*(poket->env), poket->av + 1);
	envpd = ft_calloc(i + 1, sizeof(char **));
	cpy_what_not(envpd, *(poket->env), poket->av);
	free_triple_pp(poket->env);
	*poket->env = envpd;
	set_exit_code(0 + res);
	set_global_error(0 + res);
}
