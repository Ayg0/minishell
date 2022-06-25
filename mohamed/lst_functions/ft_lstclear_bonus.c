/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_poketsclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msouiyeh <msouiyeh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 14:18:24 by msouiyeh          #+#    #+#             */
/*   Updated: 2022/06/25 15:44:43 by msouiyeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mohamed.h"

void	ft_poketsclear(t_pokets **lst, void (*del)(void *))
{
	t_pokets	*tmp;

	if (lst == NULL)
		return ;
	tmp = NULL;
	while (*lst)
	{
		tmp = *lst;
		*lst = (*lst)->next;
		ft_delpoket(tmp, del);
	}
	*lst = NULL;
}
