/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ted-dafi <ted-dafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 18:29:02 by ted-dafi          #+#    #+#             */
/*   Updated: 2022/07/01 06:24:39 by ted-dafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ted_dafi.h"

int	get_bigger_string(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] >= s2[i]);
}

void	sort_double_p(char **export, int len)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (i < len - 1)
	{
		j = 0;
		while (j < len - i - 1)
		{
			if (get_bigger_string(export[j], export[j + 1]))
			{
				tmp = export[j];
				export[j] = export[j + 1];
				export[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
}

void	display_export(t_pokets *poket)
{
	char	**export;
	int		i;

	i = 0;
	export = re_envp(*(poket->env), 0, NULL);
	sort_double_p(export, ft_count(*(poket->env), NULL, NULL));
	while (export[i])
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putendl_fd(export[i++], 1);
	}
	free_triple_pp(&export);
}

void	export(t_pokets *poket)
{
	int		i;
	char	***tmp;

	i = 1;
	if (!poket->av[1])
		return (display_export(poket));
	while (poket->av[i])
	{
		if (!all_valid(poket->av + i, 1, "export"))
		{
			i++;
			continue ;
		}
		tmp = poket->env;
		*(poket->env) = re_envp(*(poket->env), 1, poket->av[i]);
		i++;
	}
}
