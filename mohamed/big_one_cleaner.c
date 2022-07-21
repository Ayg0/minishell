/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   big_one_cleaner.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msouiyeh <msouiyeh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 01:57:14 by msouiyeh          #+#    #+#             */
/*   Updated: 2022/07/21 18:45:24 by msouiyeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mohamed.h"

char	*my_strtrim(char *s1, char *set)
{
	char	*tmp;

	tmp = ft_strtrim(s1, set);
	free(s1);
	return (tmp);
}

void	free_redirects(t_redirections *redirects)
{
	t_redirect	*tmp;

	while (redirects->read)
	{
		free(redirects->read->file_name);
		tmp = redirects->read;
		redirects->read = redirects->read->next;
		free(tmp);
	}
	while (redirects->write)
	{
		free(redirects->write->file_name);
		tmp = redirects->write;
		redirects->write = redirects->write->next;
		free(tmp);
	}
	free(redirects);
}

void	clean_big_one(t_pokets *pokets)
{
	t_pokets	*tmp;
	int			i;

	while (pokets)
	{
		i = 0;
		while (pokets->av && (pokets->av)[i])
			free((pokets->av)[i++]);
		if (pokets->av)
			free(pokets->av);
		if (pokets->path)
			free(pokets->path);
		free_redirects(pokets->redirects);
		tmp = pokets;
		pokets = pokets->next;
		free(tmp);
	}
}
