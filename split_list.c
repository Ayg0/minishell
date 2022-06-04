/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ted-dafi <ted-dafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 11:47:51 by ted-dafi          #+#    #+#             */
/*   Updated: 2022/06/04 12:17:44 by ted-dafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tokens	*ft_slpit_list(char *s, char *s2, char delimiter)
{
	int			i;
	int			n;
	t_tokens	*tokens;
	void		*previous;

	i = 0;
	tokens = NULL;
	previous = NULL;
	while (s[i])
	{
		while (s[i] && s[i] == delimiter)
			i++;
		n = i;
		if (!s[i])
			break ;
		while (s[n] && s[n] != delimiter)
			n++;
		ft_lstadd_back(&tokens, ft_lstnew(previous, ft_substr(s, i, n - i), ft_substr(s2, i, n - i)));
		previous = ft_lstlast(tokens);
		i = n;	
	}
	return (tokens);
}