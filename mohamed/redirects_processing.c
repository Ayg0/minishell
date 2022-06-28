/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects_processing.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msouiyeh <msouiyeh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 01:54:57 by msouiyeh          #+#    #+#             */
/*   Updated: 2022/06/28 01:55:29 by msouiyeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mohamed.h"

void	read_redirect(t_tokens *itire, t_pokets *poket)
{
	t_redirect	*tmp;

	tmp = NULL;
	if (ft_strlen(itire->token) == 2)
		tmp = ft_newredi(itire->next->token, 'h', O_RDONLY);
	else if (ft_strlen(itire->token) == 1)
		tmp = ft_newredi(itire->next->token, 'f', O_RDONLY);
	if (tmp == NULL)
	{
		printf("malloc faild\n");
		set_global_error(2);
	}
	ft_rediadd_back(&(poket->redirects->read), tmp);
}

void	write_redirect(t_tokens *itire, t_pokets *poket)
{
	t_redirect	*tp;

	tp = NULL;
	if (ft_strlen(itire->token) == 2)
		tp = ft_newredi(itire->next->token, 'a', O_CREAT | O_WRONLY | O_APPEND);
	else if (ft_strlen(itire->token) == 1)
		tp = ft_newredi(itire->next->token, 'f', O_CREAT | O_WRONLY | O_TRUNC);
	if (tp == NULL)
	{
		printf("malloc faild\n");
		set_global_error(2);
	}
	ft_rediadd_back(&(poket->redirects->write), tp);
}

void	delet_token(t_tokens **token)
{
	t_tokens	*tmp;

	tmp = NULL;
	if (*token)
	{
		free((*token)->token);
		free((*token)->meta_data);
		tmp = *token;
		if ((*token)->next)
			(*token)->next->previous = (*token)->previous;
		if ((*token)->previous)
			(*token)->previous->next = (*token)->next;
		if ((*token)->next != NULL)
			(*token) = (*token)->next;
		else
			(*token) = (*token)->previous;
		free(tmp);
	}
}

void	process_redirect(t_tokens **itire, t_pokets *poket)
{
	if (*((*itire)->meta_data) == 'r')
		read_redirect(*itire, poket);
	else if (*((*itire)->meta_data) == 'w')
		write_redirect(*itire, poket);
	delet_token(itire);
	delet_token(itire);
}
