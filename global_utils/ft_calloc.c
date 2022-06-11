/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ted-dafi <ted-dafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 13:12:22 by ted-dafi          #+#    #+#             */
/*   Updated: 2022/06/11 13:13:02 by ted-dafi         ###   ########.fr       */
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
		return (NULL);
	while (i)
		((char *)b)[--i] = 0;
	return (b);
}