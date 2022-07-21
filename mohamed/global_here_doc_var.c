/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global_here_doc_var.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msouiyeh <msouiyeh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 16:34:42 by msouiyeh          #+#    #+#             */
/*   Updated: 2022/07/21 16:57:20 by msouiyeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mohamed.h"

int	*global_here_doc(void)
{
	static int	code;

	return (&code);
}

int	get_global_here_doc(void)
{
	int	i;

	i = *(global_here_doc());
	return (i);
}

void	set_global_here_doc(int error)
{
	int	*p;

	p = global_here_doc();
	*p = error;
}

void	global_initializer(void)
{
	set_global_error(0);
}
