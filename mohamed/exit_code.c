/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_code.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msouiyeh <msouiyeh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 19:27:41 by msouiyeh          #+#    #+#             */
/*   Updated: 2022/06/07 19:40:10 by msouiyeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int get_exit_code(void)
{
	int i;

	i = *(exit_code());
	return (i);
}

int	*exit_code(void)
{
	static int code;
	return (&code);
}

void	set_exit_code(int status)
{
	int *p;

	p = exit_code();
	*p = status;
}