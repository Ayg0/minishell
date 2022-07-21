/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global_error_var.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ted-dafi <ted-dafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 06:48:49 by msouiyeh          #+#    #+#             */
/*   Updated: 2022/07/21 11:34:20 by ted-dafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mohamed.h"

static int	*global_error(void)
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
