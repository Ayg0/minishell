/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msouiyeh <msouiyeh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 11:11:45 by msouiyeh          #+#    #+#             */
/*   Updated: 2022/06/29 23:47:47 by msouiyeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "global_utils.h"

int	ft_strncmp(const	char	*s1, const	char	*s2, size_t	n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (n);
	while (((unsigned char *)s1)[i] == ((unsigned char *)s2)[i]
		&& s1[i] && s2[i] && i < n - 1)
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
