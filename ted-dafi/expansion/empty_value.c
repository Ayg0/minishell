/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   empty_value.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msouiyeh <msouiyeh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 17:27:30 by ted-dafi          #+#    #+#             */
/*   Updated: 2022/07/21 17:00:55 by msouiyeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ted_dafi.h"

static char	**variable(void)
{
	static char	*variable;

	return (&);
}

char	*get_variable(void)
{
	char	**val;

	val = variable();
	return (*val);
}

void	set_variable(char *value)
{
	char	**p;

	p = variable();
	*p = value;
}
