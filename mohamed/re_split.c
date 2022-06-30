/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   re_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msouiyeh <msouiyeh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 08:54:46 by msouiyeh          #+#    #+#             */
/*   Updated: 2022/06/30 14:08:47 by msouiyeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mohamed.h"

void	reattach(t_tokens **itire, t_tokens *new)
{
	t_tokens	*tmp;
	t_tokens	*tmp2;

	tmp = NULL;
	tmp2 = NULL;
	if (*itire)
	{
		free((*itire)->token);
		free((*itire)->meta_data);
		tmp = *itire;
		tmp2 = ft_lstlast(new);
		tmp2->next = (*itire)->next;
		if ((*itire)->next)
			(*itire)->next->previous = tmp2;
		new->previous = (*itire)->previous;
		if ((*itire)->previous)
			(*itire)->previous->next = new;
		*itire = tmp2;
		free(tmp);
	}
}

int	is_true_redirect(char *str)
{
	int		i;
	char	c;
	
	c = 0;
	i = 0;
	if (str[0] == 'r' || str[i] == 'w')
		c = str[0];
	else
		return (0);
	while (str[i])
	{
		if (str[i] != c)
			return (0);
		i++;
	}
	return (1);
}

t_tokens	*reseplit_helper(t_tokens *itire, int i)
{
	t_tokens	*tmp;

	tmp = NULL;
	while (itire->meta_data[++i])
	{		
		if (itire->meta_data[i] == 'b')
		{
			tmp = ft_split_list(itire->meta_data, itire->token, 'b');
			break ;
		}
	}
	return (tmp);
}

void	resplit_tokens(t_data	*data)
{
	t_tokens	*itire;
	t_tokens	*tmp;
	int			i;

	itire = data->list;
	while (itire)
	{
		i = -1;
		tmp = NULL;
		if (itire->previous && is_true_redirect(itire->previous->meta_data))
		{
			if (itire->next == NULL)
				break ;
			itire = itire->next;
			continue ;
		}
		else
			tmp = reseplit_helper(itire, i);
		if (tmp)
			reattach(&itire, tmp);
		if (itire->next == NULL)
			break ;
		itire = itire->next;
	}
	while (itire && itire->previous)
		itire = itire->previous;
	data->list = itire;
}
