/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_built_in.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msouiyeh <msouiyeh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 16:56:32 by msouiyeh          #+#    #+#             */
/*   Updated: 2022/06/30 18:14:06 by msouiyeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mohamed.h"

void	set_built_in(void	(*built_ins[8])(t_pokets *))
{
	built_ins[0] = echo;
	built_ins[1] = cd;
	built_ins[2] = pwd;
	built_ins[3] = export;
	built_ins[4] = unset;
	built_ins[5] = env;
	built_ins[6] = ft_exit;
	built_ins[7] = NULL;
}

void	launch_built_in(int	index, t_pokets *poket)
{
	void	(*built_ins[8])(t_pokets *);

	set_built_in(built_ins);
	built_ins[index](poket);
}