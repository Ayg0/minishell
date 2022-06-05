/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ted-dafi <ted-dafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 11:47:51 by ted-dafi          #+#    #+#             */
/*   Updated: 2022/06/05 18:44:21 by ted-dafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tokens	*ft_slpit_list(char *s, char *s2, char delimiter)
{
	int			i;
	int			k;
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
			while (s[k] && (k == i || s[k] == s[k - 1]))
				k++;
			ft_lstadd_back(&tokens, ft_lstnew(previous, ft_substr(s, i , k - i), ft_substr(s2, i, k - i)));
			previous = ft_lstlast(tokens);
		}
		i = k;
	}
	return (tokens);
}