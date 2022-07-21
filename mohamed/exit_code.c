/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_code.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ted-dafi <ted-dafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 19:27:41 by msouiyeh          #+#    #+#             */
/*   Updated: 2022/07/21 11:34:12 by ted-dafi         ###   ########.fr       */
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
