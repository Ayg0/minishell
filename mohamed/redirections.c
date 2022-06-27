/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msouiyeh <msouiyeh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 17:42:56 by msouiyeh          #+#    #+#             */
/*   Updated: 2022/06/27 20:53:59 by msouiyeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mohamed.h"

char	*mft_strdup(char *str)
{
	if (!str)
		return (NULL);
	return (ft_strdup(str));
}

t_redirect	*ft_newredi(char *file_name, char type, int code)
{
	t_redirect	*final;

	final = (t_redirect *)malloc(sizeof(t_redirect));
	if (final == NULL)
		return (NULL);
	final->file_name = mft_strdup(file_name);
	final->code = code;
	final->type = type;
	final->next = NULL;
	return (final);
}

t_redirect	*ft_lastredi(t_redirect *lst)
{
	if (lst)
	{
		while (lst->next)
			lst = lst->next;
	}
	return (lst);
}

void	ft_rediadd_back(t_redirect	**lst, t_redirect	*new)
{
	if (lst)
	{
		if (*lst == NULL)
			*lst = new;
		else
		{
			ft_lastredi(*lst)->next = new;
		}
	}
}

t_pokets	*allocat_pipelines(char **envp, t_data *data, t_pokets *tmp)
{
	t_tokens	*itire;
	t_pokets	*final;
	int 		i;

	final = NULL;
	itire = data->list;
	i = 1;
	while (itire)
	{
		if (*(itire->meta_data) == 'p')
			i++;
		itire = itire->next;
	}
	while (i-- > 0)
	{
		tmp = ft_new_poket(envp);
		if (tmp == NULL)
		{
			printf("malloc faild\n");
			set_global_error(2);
			return (NULL);
		}
		ft_poketadd_back(&final, tmp);
	}
	return (final);
}


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

void	process_av(t_tokens **itire, t_pokets *poket)
{
	t_tokens	*tmp;
	int 		i;

	i = 0;
	tmp = *itire;
	while (tmp && ft_strchr("prw", *(tmp->meta_data)) == 0)
	{
		i++;
		tmp = tmp->next;
	}
	poket->av = (char **)ft_calloc(i + 1, sizeof(char *));
	i = 0;
	while (ft_strchr("prw", *((*itire)->meta_data)) == 0)
	{
		(poket->av)[i] = mft_strdup((*itire)->token);
		if ((*itire)->next == NULL)
			break ;
		*itire = (*itire)->next;
		i++;
	}
	if (ft_strchr("prw", *((*itire)->meta_data)))
		*itire = (*itire)->previous;
}

void	redirection_helper(t_data	*data, t_pokets	*poket)
{
	t_tokens	*itire;

	itire = data->list;
	while (itire)
	{	
		if (*(itire->meta_data) == 'p')
			poket = poket->next;
		else
			process_av(&itire, poket);
		itire = itire->next;
	}
}

void	finish_redirections(t_data *data, t_pokets **pokets)
{
	t_tokens	*itire;
	t_pokets	*poket;

	poket = *pokets;
	itire = data->list;
	while (itire)
	{
		if (*(itire->meta_data) == 'r' || *(itire->meta_data) == 'w')
		{
			process_redirect(&itire, poket);
			continue ;
		}
		else if (*(itire->meta_data) == 'p')
			poket = poket->next;
		if (itire->next == NULL)
			break ;
		itire = itire->next;
	}
	while (itire->previous)
		itire = itire->previous;
	data->list = itire;
	redirection_helper(data, *pokets);
}

void	fill_redirections(t_pokets	**pokets, char **envp, t_data *data)
{
	*pokets = allocat_pipelines(envp, data, NULL);
	finish_redirections(data, pokets);

	// int i;
	// while ((*pokets))
	// {
	// 	printf("**************pip redirections***********\n");
	// 	printf("--------------read redirections-------------------\n");
	// 	while ((*pokets)->redirects->read)
	// 	{
	// 		printf("%s----%c\n", (*pokets)->redirects->read->file_name, (*pokets)->redirects->read->type);
	// 		(*pokets)->redirects->read = (*pokets)->redirects->read->next;
	// 	}
	// 	printf("---------------write redirections-----------------\n");
	// 	while ((*pokets)->redirects->write)
	// 	{
	// 		printf("%s----%c\n", (*pokets)->redirects->write->file_name, (*pokets)->redirects->write->type);
	// 		(*pokets)->redirects->write = (*pokets)->redirects->write->next;
	// 	}
	// 	printf("---------------argv-----------------\n");
	// 	i = 0;
	// 	while ((*pokets)->av[i])
	// 	{
	// 		printf("%s\n", (*pokets)->av[i]);
	// 		i++;
	// 	}
	// 	*pokets = (*pokets)->next;
	// }
}