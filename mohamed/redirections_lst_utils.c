/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_lst_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ted-dafi <ted-dafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 01:52:00 by msouiyeh          #+#    #+#             */
/*   Updated: 2022/06/29 17:54:24 by ted-dafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mohamed.h"

char	*mft_strdup(char *str)
{
	if (!str)
		return (NULL);
	return (ft_strdup(str));
}

t_redirect	*ft_newredi(char *file_name, char type, int code)
{
	t_redirect	*final;

	final = (t_redirect *)ft_calloc(sizeof(t_redirect), 1);
	if (final == NULL)
		return (NULL);
	final->file_name = mft_strdup(file_name);
	final->code = code;
	final->type = type;
	final->next = NULL;
	return (final);
}

t_redirect	*ft_lastredi(t_redirect *lst)
{
	if (lst)
	{
		while (lst->next)
			lst = lst->next;
	}
	return (lst);
}

void	ft_rediadd_back(t_redirect	**lst, t_redirect	*new)
{
	if (lst)
	{
		if (*lst == NULL)
			*lst = new;
		else
		{
			ft_lastredi(*lst)->next = new;
		}
	}
}
