/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msouiyeh <msouiyeh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 18:24:17 by msouiyeh          #+#    #+#             */
/*   Updated: 2022/06/10 13:14:44 by msouiyeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strjoin_all(char **s1, char *s2)
{
	size_t	s1len;
	size_t	s2len;
	char	*final;
	int		i;

	if (*s1 == NULL || s2 == NULL)
		return (ft_strdup(""));
	s1len = ft_strlen(*s1);
	s2len = ft_strlen(s2);
	final = (char *)ft_calloc(s1len + s2len + 1, sizeof(char));
	if (final == NULL)
		return (NULL);
	i = -1;
	while (s1[0][++i])
		final[i] = s1[0][i];
	i--;
	while (s2[(++i) - (int)s1len])
		final [i] = s2[i - (int)s1len];
	free(*s1);
	*s1 = NULL;
	return (final);
}
