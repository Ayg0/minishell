/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global_error_var.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ted-dafi <ted-dafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 16:34:42 by msouiyeh          #+#    #+#             */
/*   Updated: 2022/06/29 19:00:54 by ted-dafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mohamed.h"

int	*global_error(void)
{
	static int	code;

	return (&code);
}

int	get_global_error(void)
{
	int	i;

	i = *(global_error());
	return (i);
}

void	set_global_error(int error)
{
	int	*p;

	p = global_error();
	*p = error;
}

int	ft_count(char **s)
{
	int	i;

	i = 0;
	while (s && s[i])
		i++;
	return (i);
}

char **re_envp(char **envp, int flag)
{
	int		i;
	char	**final;

	i = ft_count(envp);
	final = ft_calloc(i + 1, sizeof(char *));
	i = 0;
	while (envp && envp[i])
	{
		final[i] = ft_strdup(envp[i]);
		if (flag)
			free(envp[i]);
		i++;
	}
	if (flag)
		free(envp);
	return(final);
}

char	***global_initializer(char **envp)
{
	char	***final;

	final = ft_calloc(sizeof(char **), 1);
	*final = re_envp(envp, 0);
	set_variable(NULL);
	set_global_error(0);
	set_exit_code(0);
	return (final);
}
