/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ted-dafi <ted-dafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 12:40:11 by msouiyeh          #+#    #+#             */
/*   Updated: 2022/07/21 14:45:13 by ted-dafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mohamed.h"

t_pokets	*ft_new_poket(char ***env)
{
	t_pokets		*final;
	static int		index = 1;

	final = (t_pokets *)ft_calloc(sizeof(t_pokets), 1);
	final->redirects = (t_redirections *)ft_calloc(sizeof(t_redirections), 1);
	final->redirects->read = NULL;
	final->redirects->write = NULL;
	final->index = index;
	index++;
	final->last_pid = -1;
	final->flag = 0;
	final->av = NULL;
	final->env = env;
	final->path = NULL;
	final->outfile_fd = -1;
	final->infile_fd = -1;
	final->prev = NULL;
	final->next = NULL;
	return (final);
}
