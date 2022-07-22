/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ted-dafi <ted-dafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 15:03:22 by ted-dafi          #+#    #+#             */
/*   Updated: 2022/07/22 15:46:12 by ted-dafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ted_dafi.h"

void	history(t_pokets *poket)
{
	char	*history;

	(void) poket;
	history = make_history(NULL);
	write(1, history, ft_strlen(history));
	set_exit_code(0);
	set_global_error(0);
}
