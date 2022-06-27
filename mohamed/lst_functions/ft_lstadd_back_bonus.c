/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_poketadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msouiyeh <msouiyeh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 13:20:24 by msouiyeh          #+#    #+#             */
/*   Updated: 2022/06/25 15:50:22 by msouiyeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mohamed.h"

void	ft_poketadd_back(t_pokets **lst, t_pokets	*new)
{
	if (lst != NULL)
	{
		if (*lst == NULL)
			*lst = new;
		else
		{
			new->prev = ft_lastpoket(*lst);
			ft_lastpoket(*lst)->next = new;
		}
	}
}
