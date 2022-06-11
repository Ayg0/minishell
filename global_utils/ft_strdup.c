/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ted-dafi <ted-dafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 14:19:12 by ted-dafi          #+#    #+#             */
/*   Updated: 2022/06/11 14:19:48 by ted-dafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "global_utils.h"

char	*ft_strdup(char *s1)
{
	size_t	i;
	char	*cpy;

	cpy = (char *)ft_calloc(ft_strlen(s1) + 1, sizeof(char));
	if (cpy == NULL)
		return (NULL);
	i = 0;
	while (*s1)
	{
		cpy[i++] = *s1;
		s1++;
	}
	return (cpy);
}
