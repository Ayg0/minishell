/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_delpoket_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msouiyeh <msouiyeh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 14:14:37 by msouiyeh          #+#    #+#             */
/*   Updated: 2022/06/25 15:44:43 by msouiyeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mohamed.h"

void	ft_delpoket(t_pokets *lst, void (*del)(void *))
{
	if (lst != NULL && del != NULL)
	{
		del(lst->av);
		del(lst->path);
		free((void *)lst);
	}
}
