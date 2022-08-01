/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_reworked.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msouiyeh <msouiyeh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 01:37:19 by msouiyeh          #+#    #+#             */
/*   Updated: 2022/08/01 06:05:10 by msouiyeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mohamed.h"

static	int	wc(char *s, char c)
{
	int	counter;
	int	flag;

	flag = 1;
	counter = 1;
	while (*s)
	{
		if (*s == c)
			flag = 1;
		if (flag == 1 && *s)
		{
			counter++;
			flag = 0;
		}
		if (*s)
			s++;
	}
	return (counter + 1);
}

static	char	**fill_it(char *s, char c, char **final, short flag)
{	
	int		i;
	char	ch[2];

	i = 0;
	while (*s)
	{
		if (*s == c)
			flag = !flag;
		if (*s == c && flag)
			final[i++] = ft_strdup("");
		else if (*s != c)
		{
			flag = 1;
			while (*s && *s != c)
			{
				ch[0] = *s++;
				final[i] = ult_strjoin(final[i], ch, 1);
			}
			i++;
			s--;
		}
		s++;
	}
	(!flag && !*s) && (final[i] = ft_strdup(""));
	return (final);
}

char	**ft_split_empty(char *s, char c)
{
	char	**final;

	if (s == NULL)
		return (NULL);
	final = (char **)ft_calloc(wc(s, c), sizeof(char *));
	if (final == NULL)
		return (NULL);
	final = fill_it(s, c, final, 0);
	return (final);
}

// int main(void)
// {
// 	char **str;
// 	str = ft_split_empty(":hel::lo::wor::ld:", ':');
// 	printf("%d\n",access("a.out", F_OK));
// 	printf("%d\n", wc(":hel::lo::wor::ld:", ':'));
// 	while (*str)
// 	{
// 		printf("%s$\n", *str);
// 		str++;
// 	}
// 	return 0;
// }