/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msouiyeh <msouiyeh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 13:19:33 by ted-dafi          #+#    #+#             */
/*   Updated: 2022/06/11 17:38:31 by msouiyeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "global_utils.h"
#include <stdio.h>

char	*ft_substr(char *s, int start, int len)
{
	char	*p;
	int	i;
	int	c;

	i = 0;
	if (!s)
		return (NULL);
	c = ft_strlen(s);
	if (len > c)
		len = c;
	p = (char *)ft_calloc((len + 1), sizeof(char));
	if (!p)
		return (NULL);
	if (start <= c)
	{
		while (s[i + start] && len)
		{
			p[i] = s[i + start];
			i++;
			len--;
		}
	}
	return (p);
}