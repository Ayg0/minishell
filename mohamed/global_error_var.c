/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global_error_var.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ted-dafi <ted-dafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 16:34:42 by msouiyeh          #+#    #+#             */
/*   Updated: 2022/06/28 18:13:53 by ted-dafi         ###   ########.fr       */
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

void	global_initializer(void)
{
	set_variable(NULL);
	set_global_error(0);
	set_exit_code(0);
}
