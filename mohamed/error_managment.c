/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_managment.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msouiyeh <msouiyeh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 01:58:31 by msouiyeh          #+#    #+#             */
/*   Updated: 2022/08/04 00:24:41 by msouiyeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	find_it(char *token_meta, char *charset)
{
	int	i;

	i = 0;
	while (charset[i])
	{
		if (charset[i] == *token_meta)
			return (i);
		i++;
	}
	return (-1);
}

int	check_pip(t_tokens *itire)
{
	int	len;
	int	max;

	max = itire->max;
	len = ft_strlen(itire->meta_data);
	if (!itire->next || !itire->previous || \
		ft_strchr("rw", *(itire->previous->meta_data)) != 0 || \
		ft_strlen(itire->meta_data) > 1)
	{
		error_print(itire->token, itire->max);
		set_exit_code(258);
		return (0);
	}
	return (1);
}

int	check_redirect(t_tokens *itire)
{
	int	max;
	int	len;

	max = itire->max;
	len = ft_strlen(itire->meta_data);
	if (len > max)
	{
		len = (len - max == 1) + ((len - max > 1) * max);
		error_print(&itire->token[max], len);
		return (0);
	}
	else if (!itire->next)
	{
		ft_putendl_fd("syntax error near unexpected token `newline'", 2);
		set_exit_code(258);
		return (0);
	}
	else if (ft_strchr("uqds", *(itire->next->meta_data)) == 0)
	{
		error_print(itire->next->token, itire->next->max);
		return (0);
	}
	return (1);
}

int	check_quotes(t_tokens *itire)
{
	int	i;
	int	quotes;

	i = -1;
	quotes = 0;
	while (itire->meta_data[++i])
		if (ft_strchr("sd", itire->meta_data[i]) != 0)
			quotes = !quotes;
	if (quotes)
	{
		ft_putendl_fd("syntax error unclosed quote", 2);
		set_exit_code(258);
		return (0);
	}
	return (1);
}

int	manage_errors(t_data *data)
{
	t_tokens	*itire;
	int			flag;

	itire = data->list;
	flag = 1;
	while (itire && flag)
	{
		if (*(itire->meta_data) == 'p')
			flag = check_pip(itire);
		else if (ft_strchr("wr", *(itire->meta_data)) != 0)
			flag = check_redirect(itire);
		else
			flag = check_quotes(itire);
		itire = itire->next;
	}
	return (flag);
}
