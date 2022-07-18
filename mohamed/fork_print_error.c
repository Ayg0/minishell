/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_print_error.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msouiyeh <msouiyeh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 16:09:39 by msouiyeh          #+#    #+#             */
/*   Updated: 2022/07/18 11:13:00 by msouiyeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mohamed.h"

void	fork_print_error(char *error_str)
{
	ft_putstr_fd2(ult_strjoin(error_str, "\n", 0), 2);
	set_exit_code(1);
	set_global_error(1);
}

char *ult_strjoin(char *s1, char *s2, int flag)
{
	char *final;

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

void	dup_for_built_in(t_pokets	*pokets, int *in, int *out)
{
	if (pokets->infile_fd != 0)
	{
		*in = dup(0);
		ft_dup(pokets->infile_fd, 0);
	}
	if (pokets->outfile_fd != 1)
	{	
		*out = dup(1);
		ft_dup(pokets->outfile_fd, 1);
	}
}
