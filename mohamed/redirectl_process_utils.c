/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirectl_process_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msouiyeh <msouiyeh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 09:04:38 by msouiyeh          #+#    #+#             */
/*   Updated: 2022/07/29 18:08:33 by msouiyeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mohamed.h"

int	redirection_error(char *errorstr, int flag)
{
	ft_putstr_fd(ult_strjoin(ult_strjoin("minishell: ", errorstr, 0), \
	": ambiguous redirect\n", 1), 2);
	if (flag)
		free(errorstr);
	return (0);
}

char	*red_join(char *s1, char *s2)
{
	char	*final;

	if (!s1 || !s2)
		return (NULL);
	final = ft_strjoin(s1, s2);
	return (final);
}
