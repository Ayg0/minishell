/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirectl_process_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msouiyeh <msouiyeh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 09:04:38 by msouiyeh          #+#    #+#             */
/*   Updated: 2022/07/18 11:13:00 by msouiyeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mohamed.h"

void	redirection_error(char *errorstr, int flag)
{
	ft_putstr_fd2(ult_strjoin(ult_strjoin("minishell: ", errorstr, 0), \
	": ambiguous redirect\n", 1), 2);
	if (flag)
		free(errorstr);
}

char	*red_join(char *s1, char *s2)
{
	char	*final;

	if (!s1 || !s2)
		return (NULL);
	final = ft_strjoin(s1, s2);
	return (final);
}
