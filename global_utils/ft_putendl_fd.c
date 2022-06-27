/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msouiyeh <msouiyeh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 21:36:16 by msouiyeh          #+#    #+#             */
/*   Updated: 2022/06/27 17:45:25 by msouiyeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "global_utils.h"

void	ft_putendl_fd(char *s, int fd)
{
	if (s != NULL)
	{
		ft_putstr_fd(s, fd);
		write (fd, "\n", 1);
	}
}