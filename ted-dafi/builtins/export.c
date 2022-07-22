/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ted-dafi <ted-dafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 18:29:02 by ted-dafi          #+#    #+#             */
/*   Updated: 2022/07/22 08:37:50 by ted-dafi         ###   ########.fr       */
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
		ft_putstr_fd(ft_strdup("declare -x "), 1);
		if (ft_strchr(export[i], '='))
			ft_putstr_fd(re_join(ft_substr(export[i], 0,
						ft_strchr(export[i], '=') - export[i] + 1),
					re_join(ft_strdup("\""), re_join(ft_substr(export[i],
								ft_strchr(export[i], '=') - export[i] + 1,
								ft_strlen(export[i])), ft_strdup("\"\n")))), 1);
		else
			ft_putstr_fd(re_join(ft_strdup(export[i]), ft_strdup("\n")), 1);
		i++;
	}
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
		if (!iterate_check(*(poket->av + i), 1, "export") || !flag[0])
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
