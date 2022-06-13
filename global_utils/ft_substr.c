/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msouiyeh <msouiyeh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 13:19:33 by ted-dafi          #+#    #+#             */
/*   Updated: 2022/06/13 21:39:35 by msouiyeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "global_utils.h"
#include <stdio.h>

char	*ft_substr(char *s, int start, int len)
{
	int	length;
	char	*ptr;
	int	i;

	if (s == NULL)
		return (NULL);
	i = 0;
	length = ft_strlen(s);
	if ((int)start >= length)
		length = 1;
	else if (length - (int)start > len)
		length = len + 1;
	else if (length - (int)start <= len)
		length = length - (int)start + 1;
	ptr = (char *)ft_calloc(length, 1);
	if (ptr == NULL)
		return (NULL);
	while (i < length - 1)
	{
		ptr[i] = s[i + (int)start];
		i++;
	}
	return (ptr);
}