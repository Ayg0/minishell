/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msouiyeh <msouiyeh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 18:29:02 by ted-dafi          #+#    #+#             */
/*   Updated: 2022/07/19 22:42:31 by msouiyeh         ###   ########.fr       */
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
	char	*tmp;
	int		i;

	i = 0;
	export = re_envp(*(poket->env), 0, NULL);
	sort_double_p(export, ft_count(*(poket->env), NULL, NULL));
	while (export[i])
	{
		if (i == 0)
			tmp = re_join(ft_strdup("declare -x "), ft_strdup(export[i]));
		else
			tmp = re_join(tmp, re_join(ft_strdup("declare -x "), \
					re_join(ft_strdup(export[i]), ft_strdup("\n"))));
		i++;
	}
	ft_putstr_fd(tmp, 2);
	free_triple_pp(&export);
}

int	set_zero(void)
{
	set_exit_code(0);
	set_global_error(0);
	return (1);
}

void	export(t_pokets *poket)
{
	int		i;
	int		flag[2];
	char	***tmp;

	i = 1;
	flag[1] = 0;
	if (!poket->av[1])
		return (display_export(poket));
	while (poket->av[i])
	{
		flag[0] = ft_strncmp("_=", poket->av[i], 2);
		if (!all_valid(poket->av + i, 1, "export") || !flag[0])
		{
			flag[1] = !flag[0];
			i++;
			continue ;
		}
		tmp = poket->env;
		*(poket->env) = re_envp(*(poket->env), 1, poket->av[i]);
		i++;
	}
	flag[1] && set_zero();
}
