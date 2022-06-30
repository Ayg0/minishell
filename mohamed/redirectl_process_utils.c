/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirectl_process_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msouiyeh <msouiyeh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 09:04:38 by msouiyeh          #+#    #+#             */
/*   Updated: 2022/06/30 09:05:19 by msouiyeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mohamed.h"

void	redirection_error(char *errorstr, int flag)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(errorstr, 2);
	ft_putendl_fd(": ambiguous redirect", 2);
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
