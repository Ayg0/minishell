/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ted-dafi <ted-dafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 13:19:33 by ted-dafi          #+#    #+#             */
/*   Updated: 2022/06/16 09:45:10 by ted-dafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "global_utils.h"
#include <stdio.h>

char	*ft_substr(char *s, int start, int len)
{
	int		length;
	char	*ptr;
	int		i;

	if (s == NULL)
		return (NULL);
	i = 0;
	length = ft_strlen(s);
	if (start >= length)
		length = 1;
	else if (length - start > len)
		length = len + 1;
	else if (length - start <= len)
		length = length - start + 1;
	ptr = (char *)ft_calloc(length, 1);
	if (ptr == NULL)
		return (NULL);
	while (i < length - 1)
	{
		ptr[i] = s[i + start];
		i++;
	}
	return (ptr);
}
