/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_scout.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ted-dafi <ted-dafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 12:36:22 by ted-dafi          #+#    #+#             */
/*   Updated: 2022/06/16 09:43:08 by ted-dafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "global_utils.h"

int	env_scout(char *str, char *var)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != var[i])
			break ;
		i++;
	}
	if (str[i] == '=' && !var[i])
		return (i + 1);
	return (-1);
}
