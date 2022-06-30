/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_exp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msouiyeh <msouiyeh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 11:20:40 by ted-dafi          #+#    #+#             */
/*   Updated: 2022/06/30 09:31:05 by msouiyeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ted_dafi.h"

int	check_if_blank(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] && s[i] != ' ' && s[i] != '\t')
			return (0);
		i++;
	}
	return (1);
}

char	*get_exp(char *var, char c, char **envp)
{
	int		i;
	int		j;
	char	*ret_value;

	ret_value = NULL;
	if (!envp)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		j = env_scout(envp[i], var);
		if (j != -1)
		{
			ret_value = ft_substr(envp[i], j, ft_strlen(envp[i]) - j);
			if (c != 'q' && check_if_blank(ret_value))
				break ;
			free(var);
			return (ret_value);
		}
		i++;
	}
	if (!get_variable())
		set_variable(ft_strdup(var));
	free(var);
	return (ret_value);
}
