/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ted-dafi <ted-dafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 13:12:22 by ted-dafi          #+#    #+#             */
/*   Updated: 2022/07/22 15:19:45 by ted-dafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "global_utils.h"

void	*ft_calloc(int count, int size)
{
	void	*b;
	int		i;

	i = count * size;
	b = malloc(i);
	if (!b)
	{
		put_history();
		exit(write(2, "Memory allocation failure\n", 26));
	}
	while (i)
		((char *)b)[--i] = 0;
	return (b);
}
