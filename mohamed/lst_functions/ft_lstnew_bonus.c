/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msouiyeh <msouiyeh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 12:40:11 by msouiyeh          #+#    #+#             */
/*   Updated: 2022/06/28 02:13:16 by msouiyeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mohamed.h"

t_pokets	*ft_new_poket(char **env)
{
	t_pokets		*final;
	static int		index = 1;

	final = (t_pokets *)malloc(sizeof(t_pokets));
	if (final == NULL)
		return (NULL);
	final->redirects = (t_redirections *)malloc(sizeof(t_redirections));
	if (final->redirects == NULL)
		return (NULL);
	final->redirects->read = NULL;
	final->redirects->write = NULL;
	final->index = index;
	index++;
	final->av = NULL;
	final->env = env;
	final->path = NULL;
	final->outfile_fd = -1;
	final->infile_fd = -1;
	final->prev = NULL;
	final->next = NULL;
	return (final);
}
