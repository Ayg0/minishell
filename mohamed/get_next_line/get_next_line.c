/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msouiyeh <msouiyeh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 18:24:42 by msouiyeh          #+#    #+#             */
/*   Updated: 2022/06/10 13:20:47 by msouiyeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_substr_g(char *s, unsigned int start, size_t len)
{
	size_t	length;
	char	*ptr;
	size_t	i;

	if (s == NULL)
		return (NULL);
	i = 0;
	length = ft_strlen(s);
	if ((size_t)start >= length)
		length = 1;
	else if (length - (size_t)start > len)
		length = len + 1;
	else if (length - (size_t)start <= len)
		length = length - (size_t)start + 1;
	ptr = (char *)ft_calloc(length, 1);
	if (ptr == NULL)
		return (NULL);
	while (i < length - 1)
	{
		ptr[i] = s[i + (size_t)start];
		i++;
	}
	return (ptr);
}

char	*handel_the_shit(char	**saved)
{
	char	*final;
	char	*tp;
	int		i;

	i = ft_strlen(*saved);
	final = NULL;
	if (ft_strchr(*saved, '\n'))
	{
		final = ft_substr_g(*saved, 0, ft_strchr(*saved, '\n') - *saved + 1);
		tp = *saved;
		*saved = ft_substr_g(*saved, ft_strchr(*saved, '\n') - *saved + 1, i);
		free_it(&tp);
		return (final);
	}
	else
	{
		final = ft_strdup(*saved);
		free_it(saved);
		return (final);
	}
}

char	*free_it(char	**target)
{
	free(*target);
	*target = NULL;
	return (NULL);
}

char	*get_next_line(int fd)
{
	char		str[BUFFER_SIZE + 1];
	static char	*saved;
	char		*final;
	int			re_ad;

	re_ad = 1;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!saved)
		saved = ft_strdup("");
	while (re_ad > 0 && !ft_strchr(saved, '\n'))
	{
		re_ad = read(fd, str, BUFFER_SIZE);
		if (re_ad < 0)
			return (free_it(&saved));
		str[re_ad] = '\0';
		saved = ft_strjoin_all(&saved, str);
	}
	final = handel_the_shit(&saved);
	if (final && !ft_strlen(final))
		free_it(&final);
	return (final);
}

// #include <stdio.h>

// int	main(void)
// {

// 	int	fd = open("files/41_no_nl", O_RDONLY);
// 	// int	fd = open("files/41_no_nl", O_RDONLY);
// //	char *ret;
// //	ret = get_next_line(fd);
// 	int i = 0;
// 	char *line;
// 	while (i < 5)
// 	{
// 		line = get_next_line(fd);
// 		printf("|%s|",line);
// 		free(line);
// 		i++;
// 	}
// }