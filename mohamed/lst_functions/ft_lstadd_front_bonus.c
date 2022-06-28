/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msouiyeh <msouiyeh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 12:52:39 by msouiyeh          #+#    #+#             */
/*   Updated: 2022/06/28 02:12:54 by msouiyeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mohamed.h"

void	ft_poketadd_front(t_pokets	**lst, t_pokets	*new)
{
	if (!lst || !new)
		return ;
	new->next = *lst;
	new->prev = ft_lastpoket(*lst);
	*lst = new;
}
