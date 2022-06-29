/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ted-dafi <ted-dafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 09:23:01 by ted-dafi          #+#    #+#             */
/*   Updated: 2022/06/29 17:59:26 by ted-dafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ted_dafi.h"

t_tokens	*ft_lstnew(t_tokens *previous, void *meta, char *token)
{
	t_tokens	*new;

	new = (t_tokens *)ft_calloc(sizeof(t_tokens), 1);
	(*new).meta_data = meta;
	(*new).token = token;
	(*new).next = NULL;
	(*new).previous = previous;
	return (new);
}

t_tokens	*ft_lstlast(t_tokens *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_lstadd_back(t_tokens **lst, t_tokens *new)
{
	if (!(*lst))
		*lst = new;
	else
		ft_lstlast(*lst)->next = new;
}
