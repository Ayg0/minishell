/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects_processing.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msouiyeh <msouiyeh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 01:54:57 by msouiyeh          #+#    #+#             */
/*   Updated: 2022/07/26 17:58:38 by msouiyeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mohamed.h"

void	read_redirect(t_tokens *itire, t_pokets *poket)
{
	t_redirect	*tmp;

	tmp = NULL;
	if (access(itire->next->token, W_OK) == -1)
	{
		if (access(itire->next->token, F_OK) == -1)
			ft_putstr_fd(ult_strjoin("minishell: ", \
				ult_strjoin(itire->next->token, \
				": No such file or directory\n", 0), 2), 2);
		else
			ft_putstr_fd(ult_strjoin("minishell: ", \
				ult_strjoin(itire->next->token, \
				": Permission denied\n", 0), 2), 2);
		poket->index = -1;
		set_global_error(1);
		set_exit_code(1);
		return ;
	}
	if (ft_strlen(itire->token) == 2)
		tmp = ft_newredi(itire->next->token, 'h', O_RDONLY);
	else if (ft_strlen(itire->token) == 1)
		tmp = ft_newredi(itire->next->token, 'f', O_RDONLY);
	ft_rediadd_back(&(poket->redirects->read), tmp);
}

void	write_redirect(t_tokens *itire, t_pokets *poket)
{
	t_redirect	*tp;
	int			tmp;

	tp = NULL;
	if (ft_strlen(itire->token) == 2)
		tp = ft_newredi(itire->next->token, 'a', O_CREAT | O_WRONLY | O_APPEND);
	else if (ft_strlen(itire->token) == 1)
		tp = ft_newredi(itire->next->token, 'f', O_CREAT | O_WRONLY | O_TRUNC);
	ft_rediadd_back(&(poket->redirects->write), tp);
	tmp = open(tp->file_name, tp->code, 0666);
	if (tmp == -1)
	{
		ft_putstr_fd(ult_strjoin("minishell: faild to open "\
		, ult_strjoin(tp->file_name, "\n", 0), 2), 2);
		poket->index = -1;
		set_global_error(1);
		set_exit_code(1);
		return ;
	}
	close(tmp);
}

int	check_opperand_errors(t_tokens *itire)
{
	int	i;

	i = 0;
	if (itire->meta_data[0] == 'b'\
			|| itire->meta_data[ft_strlen(itire->meta_data) - 1] == 'b')
	{
		itire->meta_data = my_strtrim(itire->meta_data, "b");
		itire->token = my_strtrim(itire->token, " \t\n");
		if (itire->token[0] == '\0')
			itire->flag = -505;
	}
	if (itire->meta_data[0] == '\0' && (itire->flag == -505 || itire->flag == -404))
	{
		redirection_error(itire->old_token, 0);
		return (0);
	}
	while (itire->meta_data[i])
	{
		if (itire->meta_data[i++] == 'b')
		{
			redirection_error(itire->old_token, 0);
			return (0);
		}
	}
	return (1);
}

void	delet_token(t_tokens **token)
{
	t_tokens	*tmp;

	tmp = NULL;
	if (*token)
	{
		free((*token)->token);
		(*token)->token = NULL;
		free((*token)->old_token);
		(*token)->old_token = NULL;
		free((*token)->meta_data);
		(*token)->meta_data = NULL;
		tmp = *token;
		if ((*token)->next)
			(*token)->next->previous = (*token)->previous;
		if ((*token)->previous)
			(*token)->previous->next = (*token)->next;
		if ((*token)->next != NULL)
			(*token) = (*token)->next;
		else
			(*token) = (*token)->previous;
		free (tmp);
	}
}

void	process_redirect(t_tokens **itire, t_pokets *poket)
{
	if (check_opperand_errors((*itire)->next) == 0)
	{
		poket->index = -1;
		set_global_error(1);
		set_exit_code(1);
		delet_token(itire);
		delet_token(itire);
		return ;
	}
	if (get_global_error() == 1)
		set_global_error(0);
	if (*((*itire)->meta_data) == 'r')
		read_redirect(*itire, poket);
	else if (*((*itire)->meta_data) == 'w')
		write_redirect(*itire, poket);
	delet_token(itire);
	delet_token(itire);
}
