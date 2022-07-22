/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ted-dafi <ted-dafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 20:30:46 by ted-dafi          #+#    #+#             */
/*   Updated: 2022/07/22 15:38:45 by ted-dafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_stroin(char **s1, char *s2)
{
	char		*s3;
	size_t		i;
	size_t		j;

	if (!(*s1))
		return (ft_strdup(s2));
	i = 0;
	j = 0;
	s3 = (char *)ft_calloc(ft_stlen(*s1) + ft_stlen(s2) + 1, sizeof(char));
	if (!s3)
		return (NULL);
	while (s1[0][i])
		s3[j++] = s1[0][i++];
	i = 0;
	my_free(s1, NULL, 0);
	while (s2[i])
		s3[j++] = s2[i++];
	return (s3);
}

int	ft_newlchr(const char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (-1);
	while (s[i])
	{
		if (s[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}
