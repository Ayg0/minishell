/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_q_remov.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msouiyeh <msouiyeh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 01:43:45 by msouiyeh          #+#    #+#             */
/*   Updated: 2022/06/28 01:44:14 by msouiyeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mohamed.h"

char	*remove_limiter_q(char *limiter)
{
	int		i;
	char	c[2];
	char	*final;
	char	*meta;

	meta = get_meta(limiter);
	final = ft_strdup("");
	c[1] = 0;
	i = 0;
	while (limiter[i])
	{
		if (meta[i] == 'd' || meta[i] == 's')
			i++;
		else
		{
			c[0] = limiter[i];
			final = here_doc_join(final, c, 0);
			i++;
		}
	}
	free(meta);
	return (final);
}
