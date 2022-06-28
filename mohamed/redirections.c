/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ted-dafi <ted-dafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 17:42:56 by msouiyeh          #+#    #+#             */
/*   Updated: 2022/06/28 18:07:23 by ted-dafi         ###   ########.fr       */
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
		else
			process_av(&itire, poket);
		itire = itire->next;
	}
}

void	reattach(t_tokens **itire, t_tokens *new)
{
	t_tokens	*tmp;

	tmp = NULL;
	if (*itire)
	{
		free((*itire)->token);
		free((*itire)->meta_data);
		tmp = *itire;
		ft_lstlast(new)->next = (*itire)->next;
		if ((*itire)->next)
			(*itire)->next->previous = ft_lstlast(new);
		new->previous = (*itire)->previous;
		if ((*itire)->previous)
			(*itire)->previous->next = new;
		*itire = ft_lstlast(new);
		free(tmp);
	}
}

void	resplit_tokens(t_data	*data)
{
	t_tokens	*itire;
	t_tokens	*tmp;
	int			i;

	i = -1;
	tmp = NULL;
	itire = data->list;
	while (itire)
	{
		while (itire->meta_data[++i])
			if (itire->meta_data[i] == 'b')
			{
				tmp = ft_split_list(itire->meta_data, itire->token, 'b');
				break ;	
			}
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
	//resplit_tokens(data);
	//redirection_helper(data, *pokets);
}

void	fill_redirections(t_pokets	**pokets, char **envp, t_data *data)
{
	*pokets = allocat_pipelines(envp, data, NULL);
	finish_redirections(data, pokets);
}
