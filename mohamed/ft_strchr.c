/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msouiyeh <msouiyeh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 15:40:57 by msouiyeh          #+#    #+#             */
/*   Updated: 2022/06/10 12:59:22 by msouiyeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if (*s == c)
		return ((char *)s);
	return (NULL);
}

char	*ft_strdup(char *s1)
{
	size_t	i;
	char	*cpy;

	cpy = (char *)ft_calloc(ft_strlen(s1) + 1, sizeof(char));
	if (cpy == NULL)
		return (0);
	i = 0;
	while (*s1)
	{
		cpy[i++] = *s1;
		s1++;
	}
	return (cpy);
}