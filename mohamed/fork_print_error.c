/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_print_error.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msouiyeh <msouiyeh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 16:09:39 by msouiyeh          #+#    #+#             */
/*   Updated: 2022/07/29 10:16:28 by msouiyeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mohamed.h"

void	fork_print_error(char *error_str)
{
	ft_putstr_fd(ult_strjoin(error_str, "\n", 0), 2);
	set_exit_code(1);
	set_global_error(1);
}

char	*ult_strjoin(char *s1, char *s2, int flag)
{
	char	*final;

	if (s1 == NULL)
		return (NULL);
	if (s2 == NULL)
		return (NULL);
	final = ft_strjoin(s1, s2);
	if (flag == 1 || flag == 3)
		free(s1);
	if (flag == 2 || flag == 3)
		free(s2);
	return (final);
}
