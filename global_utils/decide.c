/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   decide.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ted-dafi <ted-dafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 13:18:27 by ted-dafi          #+#    #+#             */
/*   Updated: 2022/07/31 15:00:09 by ted-dafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "global_utils.h"
#include <stdio.h>

char	decide(char *main_str, char *mirror_str, char c, char def)
{
	int	i;

	i = 0;
	while (main_str[i])
	{
		if (main_str[i] == c)
			return (mirror_str[i]);
		i++;
	}
	return (def);
}
