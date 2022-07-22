/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_built_in.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ted-dafi <ted-dafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 16:56:32 by msouiyeh          #+#    #+#             */
/*   Updated: 2022/07/22 15:01:41 by ted-dafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mohamed.h"

void	set_built_in(void (*built_ins[9])(t_pokets *))
{
	built_ins[0] = echo;
	built_ins[1] = cd;
	built_ins[2] = pwd;
	built_ins[3] = export;
	built_ins[4] = unset;
	built_ins[5] = env;
	built_ins[6] = ft_exit;
	built_ins[7] = history;
	built_ins[8] = NULL;
}

void	launch_built_in(int index, t_pokets *poket)
{
	void	(*built_ins[9])(t_pokets *);

	set_built_in(built_ins);
	built_ins[index](poket);
}
