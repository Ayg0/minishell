/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   empty_value.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ted-dafi <ted-dafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 17:27:30 by ted-dafi          #+#    #+#             */
/*   Updated: 2022/06/28 18:19:51 by ted-dafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ted_dafi.h"

char	**variable(void)
{
	static char	*variable;

	return (&variable);
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