/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ted-dafi <ted-dafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 11:47:51 by ted-dafi          #+#    #+#             */
/*   Updated: 2022/06/06 10:24:11 by ted-dafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_serch(char c, char c2, char *elements)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (elements[++i])
		j += (elements[i] == c) + (elements[i] == c2);
	return (j);
}

int	meta_checker(char *s, char in_need, int k)
{
	if (!s[k] || s[k] == 'b')
		return (0);
	else if ((decide("prw","|<>", s[k]) != 'u') && s[k] != in_need)
		return (0);
	else if (ft_serch(s[k], in_need, "uqds") == 1)
		return(0);
	return (1);
}

t_tokens	*ft_slpit_list(char *s, char *s2, char delimiter)
{
	int			i;
	int			 k;
	t_tokens	*tokens;
	void		*previous;

	i = 0;
	tokens = NULL;
	previous = NULL;
	while (s[i])
	{
		while (s[i] && s[i] == delimiter)
			i++;
		if (!s[i])
			break ;
		k = i;
		while (s[k] && s[k] != delimiter)
		{
			i = k;
			while(k == 0 || meta_checker(s, s[i], k))
				k++;
			ft_lstadd_back(&tokens, ft_lstnew(previous, ft_substr(s, i , k - i), ft_substr(s2, i, k - i)));
			previous = ft_lstlast(tokens);
			if (s[k] == ' ')
				break ;
		}
		i = k;
	}
	return (tokens);
}