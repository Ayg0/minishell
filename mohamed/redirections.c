/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msouiyeh <msouiyeh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 17:42:56 by msouiyeh          #+#    #+#             */
/*   Updated: 2022/06/28 21:56:02 by msouiyeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mohamed.h"

t_pokets	*allocat_pipelines(char **envp, t_data *data, t_pokets *tmp)
{
	t_tokens	*itire;
	t_pokets	*final;
	int			i;

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

void	process_av(t_tokens **itire, t_pokets *poket)
{
	t_tokens	*tmp;
	int			i;

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
		else if (*(itire->meta_data) != '\0')
			process_av(&itire, poket);
		itire = itire->next;
	}
}

void	reattach(t_tokens **itire, t_tokens *new)
{
	t_tokens	*tmp;
	t_tokens	*tmp2;

	tmp = NULL;
	tmp2 = NULL;
	if (*itire)
	{
		free((*itire)->token);
		free((*itire)->meta_data);
		tmp = *itire;
		tmp2 = ft_lstlast(new);
		tmp2->next = (*itire)->next;
		if ((*itire)->next)
			(*itire)->next->previous = tmp2;
		new->previous = (*itire)->previous;
		if ((*itire)->previous)
			(*itire)->previous->next = new;
		*itire = tmp2;
		free(tmp);
	}
}

void	resplit_tokens(t_data	*data)
{
	t_tokens	*itire;
	t_tokens	*tmp;
	int			i;

	itire = data->list;
	while (itire)
	{
		i = -1;
		tmp = NULL;
		while (itire->meta_data[++i])
			if (itire->meta_data[i] == 'b')
			{
				tmp = ft_split_list(itire->meta_data, itire->token, 'b');
				break ;	
			}
		if (tmp)
			reattach(&itire, tmp);
		if (itire->next == NULL)
			break ;
		itire = itire->next;
	}
	while (itire && itire->previous)
		itire = itire->previous;
	data->list = itire;
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
			if (get_global_error() != 0)
				return ;
			continue ;
		}
		else if (*(itire->meta_data) == 'p')
			poket = poket->next;
		if (itire->next == NULL)
			break ;
		itire = itire->next;
	}
	while (itire && itire->previous)
		itire = itire->previous;
	data->list = itire;
	resplit_tokens(data);
	redirection_helper(data, *pokets);
}

void	fill_redirections(t_pokets	**pokets, char **envp, t_data *data)
{
	*pokets = allocat_pipelines(envp, data, NULL);
	finish_redirections(data, pokets);
}
