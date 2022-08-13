/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msouiyeh <msouiyeh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 12:55:37 by ted-dafi          #+#    #+#             */
/*   Updated: 2022/08/12 18:44:44 by msouiyeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "global_utils.h"

// this is a bomb use it at your own risk no free no protection
char	*ft_strjoin(char *s1, char *s2)
{
	char		*s3;
	int			i;
	int			j;
	int			k;

	j = ft_strlen(s1);
	k = ft_strlen(s2);
	s3 = (char *)ft_calloc((j + k + 1), sizeof(char));
	if (!s3)
		return (NULL);
	i = -1;
	while (++i < j)
		s3[i] = s1[i];
	i = -1;
	while (++i < k)
		s3[i + j] = s2[i];
	return (s3);
}
