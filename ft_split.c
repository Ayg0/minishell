/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ted-dafi <ted-dafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 19:03:32 by ted-dafi          #+#    #+#             */
/*   Updated: 2022/05/23 19:03:43 by ted-dafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	tha_nambar(char *s, char c)
{
	size_t	i;

	i = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (!*s)
			break ;
		while (*s != c && *s)
			s++;
		i++;
	}
	return (i);
}

static char	*ft_look_for(char *s, int c)
{
	while (*s)
	{
		if (*s == (unsigned char )c)
			return ((char *)s);
		s++;
	}
	return ((char *)s);
}

void	why_r_ya_running(char **d, int i)
{
	while (i >= 0)
		free(d[i--]);
	free(d);
}

static void	doo_it(char **da, char *from, char c)
{
	size_t	w;
	int		i;

	i = 0;
	while (*from)
	{
		while (*from == c)
			from++;
		if (*from)
		{
			w = (size_t)(ft_look_for(from, c) - (char *)from);
			*da = (char *)ft_calloc((w + 1), sizeof(char));
			if (!da)
			{
				why_r_ya_running(da, i);
				return ;
			}
			ft_strlcpy(*da, from, w + 1);
			da++;
			i++;
			from += w;
		}
	}
}

char	**ft_split(char *s, char c)
{
	char	**p;

	if (!s || !ft_strlen(s))
		exit(write(2, "Error\n", 7));
	p = (char **)ft_calloc((tha_nambar(s, c) + 1), sizeof(char *));
	if (!p)
		return (NULL);
	doo_it(p, s, c);
	return (p);
}
