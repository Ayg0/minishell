/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_code.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msouiyeh <msouiyeh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 19:27:41 by msouiyeh          #+#    #+#             */
/*   Updated: 2022/08/04 01:31:17 by msouiyeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	*exit_code(void)
{
	static int	code;

	return (&code);
}

int	get_exit_code(void)
{
	int	i;

	i = *(exit_code());
	return (i);
}

void	set_exit_code(int status)
{
	int	*p;

	p = exit_code();
	*p = status;
}
