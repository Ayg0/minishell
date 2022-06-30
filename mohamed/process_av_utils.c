/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_av_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msouiyeh <msouiyeh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 16:24:08 by msouiyeh          #+#    #+#             */
/*   Updated: 2022/06/30 16:24:23 by msouiyeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mohamed.h"

void	process_av_help(t_tokens **itire, t_pokets *poket)
{
	int	i;

	i = 0;
	while ((*itire) && ft_strchr("prw", *((*itire)->meta_data)) == 0)
	{
		(poket->av)[i] = mft_strdup((*itire)->token);
		if ((*itire)->next == NULL)
			break ;
		*itire = (*itire)->next;
		if ((*itire) && *((*itire)->meta_data) == '\0' && \
			(*itire)->flag == -404)
		{
			if ((*itire)->next == NULL)
				break ;
			*itire = (*itire)->next;
		}
		i++;
	}
}
