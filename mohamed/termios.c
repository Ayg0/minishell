/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termios.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msouiyeh <msouiyeh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 22:45:24 by msouiyeh          #+#    #+#             */
/*   Updated: 2022/07/27 00:01:38 by msouiyeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mohamed.h"

void	terminal_error(char *str, char *free_it)
{
	ft_putendl_fd(str, 2);
	free(free_it);
	set_global_error(1);
}

int	set_termios_attr(void)
{
	struct termios tty;

	tcgetattr(0, &tty);
	tty.c_lflag &= ~ECHOCTL;
	tcsetattr(0, 0, &tty);
	return (1);
}

int	resettermios_attr(void)
{
	struct termios tty;

	tcgetattr(0, &tty);
	tty.c_lflag |= ECHOCTL;
	tcsetattr(0, 0, &tty);
	return (1);
}

void	initialise(void)
{
	set_global_error(0);
	set_termios_attr();	
}
