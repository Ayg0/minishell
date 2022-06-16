/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   decide.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ted-dafi <ted-dafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 13:18:27 by ted-dafi          #+#    #+#             */
/*   Updated: 2022/06/16 09:42:41 by ted-dafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "global_utils.h"

char	decide(char *main_str, char *mirror_str, char c)
{
	int	i;

	i = 0;
	while (main_str[i])
	{
		if (main_str[i] == c)
			return (mirror_str[i]);
		i++;
	}
	return ('u');
}
