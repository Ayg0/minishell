/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_av_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ted-dafi <ted-dafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 16:24:08 by msouiyeh          #+#    #+#             */
/*   Updated: 2022/06/30 21:36:07 by ted-dafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mohamed.h"

void	process_av_help(t_tokens **itire, t_pokets *poket)
{
	char	**tmp;
	int		i;
	int		j;

	i = 0;
	while ((*itire) && is_true_pip((*itire)->meta_data) == 0)
	{
		if (ft_strchr((*itire)->meta_data, 'b'))
		{
			tmp = ft_split((*itire)->token, ' ');
			j = -1;
			while (tmp && tmp[++j])
			{
				(poket->av)[i++] = mft_strdup(tmp[j]);
				free(tmp[j]);
			}
			free(tmp);
			tmp = NULL;
		}
		else
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
