/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pstrjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ted-dafi <ted-dafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 13:36:51 by msouiyeh          #+#    #+#             */
/*   Updated: 2022/06/29 17:41:49 by ted-dafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_alloc(int size)
{
	char	*re;

	if (size == 1)
	{
		re = (char *)ft_calloc(sizeof(char), 1);
		return (re);
	}
	re = (char *)ft_calloc(sizeof(char) * size, 1);
	if (re == NULL)
		return (0);
	return (re);
}

int	ft_count_len(int size, char **strs, char *sep)
{
	int	i;
	int	counter;
	int	l;
	int	j;

	l = 0;
	i = -1;
	counter = 0;
	if (size == 0)
		return (1);
	while (++i < size)
	{
		j = 0;
		while (strs[i][j++] != '\0')
			counter++;
	}
	while (*sep)
	{
		l++;
		sep++;
	}
	counter = counter + (l * (size - 1));
	return (counter + 1);
}

void	ft_fill_str(int size, char **strs, char *sep, char **result)
{
	int	i;
	int	j;
	int	s;
	int	r;

	i = -1;
	r = 0;
	while (++i < size)
	{
		j = 0;
		while (strs[0][j] != '\0')
			result[0][r++] = strs[0][j++];
		s = 0;
		if (i < size - 1)
			while (sep[s])
				result[0][r++] = sep[s++];
		strs++;
	}
	result[0][r] = '\0';
}

char	*ft_pstrjoin(int size, char **strs, char *sep)
{
	char	*result;
	int		alloc_size;

	alloc_size = ft_count_len(size, strs, sep);
	result = ft_alloc(alloc_size);
	ft_fill_str(size, strs, sep, &result);
	return (result);
}
