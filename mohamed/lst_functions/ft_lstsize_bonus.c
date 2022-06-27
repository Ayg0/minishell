/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msouiyeh <msouiyeh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 13:09:24 by msouiyeh          #+#    #+#             */
/*   Updated: 2022/06/25 15:53:17 by msouiyeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mohamed.h"

int	ft_poketsize(t_pokets *lst)
{
	int	i;

	i = 1;
	if (lst == NULL)
		return (0);
	while (lst->next)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}
