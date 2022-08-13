/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_av_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msouiyeh <msouiyeh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 16:24:08 by msouiyeh          #+#    #+#             */
/*   Updated: 2022/08/11 22:35:34 by msouiyeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mohamed.h"

void	help_process_av(t_tokens **itire, t_pokets *poket, int *i)
{
	char	**tmp;
	int		j;

	tmp = ft_split((*itire)->token, ' ');
	j = -1;
	while (tmp && tmp[++j])
	{
		(poket->av)[(*i)++] = mft_strdup(tmp[j]);
		free(tmp[j]);
	}
	free(tmp);
	tmp = NULL;
}

void	process_av_help(t_tokens **itire, t_pokets *poket)
{
	int		i;

	i = 0;
	while ((*itire) && is_true_cntl((*itire)->meta_data, 'p') == 0)
	{
		if (ft_strchr((*itire)->meta_data, 'b'))
			help_process_av(itire, poket, &i);
		else if ((*itire)->flag != -404)
			(poket->av)[i++] = mft_strdup((*itire)->token);
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
	}
}
