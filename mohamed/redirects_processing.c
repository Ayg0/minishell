/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects_processing.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msouiyeh <msouiyeh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 01:54:57 by msouiyeh          #+#    #+#             */
/*   Updated: 2022/06/30 00:06:17 by msouiyeh         ###   ########.fr       */
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
	char *final;

	if (!s1 || !s2)
		return (NULL);
	final = ft_strjoin(s1, s2);
	return (final);	
}
int	check_opperand_errors(t_tokens *itire)
{
	int i;

	i = 0;
	while (itire->meta_data[i])
	{
		if (itire->meta_data[i] == 'b')
		{
			redirection_error(itire->token, 0);
			return (0);
		}
		i++;
	}
	if (*(itire->meta_data) == '\0' && *(itire->token) == '\0' && get_variable())
	{
		redirection_error(red_join("$", get_variable()), 1);
		return (0);	
	}
	return (1);
}

void	process_redirect(t_tokens **itire, t_pokets *poket)
{
	if (check_opperand_errors((*itire)->next) == 0)
	{
		set_exit_code(3);
		return ;
	}
	if (*((*itire)->meta_data) == 'r')
		read_redirect(*itire, poket);
	else if (*((*itire)->meta_data) == 'w')
		write_redirect(*itire, poket);
	delet_token(itire);
	delet_token(itire);
}
