/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   empty_value.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ted-dafi <ted-dafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 17:27:30 by ted-dafi          #+#    #+#             */
/*   Updated: 2022/06/28 17:30:41 by ted-dafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ted_dafi.h"

#include "../minishell.h"

char	*variable(void)
{
	static char	*variable;

	return (variable);
}

char	*get_variable(void)
{
	char	*val;

	val = exit_code();
	return (val);
}

void	set_variable(char *value)
{
	char	*p;

	p = variable();
	*p = value;
}