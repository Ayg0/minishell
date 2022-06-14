/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   re_join.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ted-dafi <ted-dafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 11:17:28 by ted-dafi          #+#    #+#             */
/*   Updated: 2022/06/14 12:59:30 by ted-dafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ted_dafi.h"

char	*re_join(char *s1, char *s2)
{
	char	*comb_s;

	if (!s1)
		return (s2);
	if (!s2)
		return (s1);
	comb_s = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	return (comb_s);
}
