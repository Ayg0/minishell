/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msouiyeh <msouiyeh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 17:42:56 by msouiyeh          #+#    #+#             */
/*   Updated: 2022/06/30 16:13:02 by msouiyeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mohamed.h"

t_pokets	*allocat_pipelines(char ***envp, t_data *data)
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
		ft_poketadd_back(&final, ft_new_poket(envp));
	return (final);
}

void	process_av_help(t_tokens **itire, t_pokets *poket)
{
	int	i;

	i = 0;
	while ((*itire) && ft_strchr("prw", *((*itire)->meta_data)) == 0)
	{
		(poket->av)[i] = mft_strdup((*itire)->token);
		if ((*itire)->next == NULL)
			break ;
		*itire = (*itire)->next;
		if ((*itire) && *((*itire)->meta_data) == '\0' && (*itire)->flag == -404)
		{
			if ((*itire)->next == NULL)
				break ;
			*itire = (*itire)->next;
		}
		i++;
	}
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
	process_av_help(itire, poket);
	if (*itire && ft_strchr("prw", *((*itire)->meta_data)))
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
		else if (*(itire->meta_data) == '\0' && itire->flag == -404)
		{
			itire = itire->next;
			continue ;
		}
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
}

void	fill_redirections(t_pokets	**pokets, char ***envp, t_data *data)
{
	resplit_tokens(data);
	// while (data->list)
	// {
	// 	printf("%s      %s\n", data->list->token, data->list->meta_data);
	// 	data->list = data->list->next;
	// 	set_global_error(1);
	// }
	// return ;
	// if (*(data->list->meta_data) == '\0' && data->list->flag == -404)
	// {
	// 	set_global_error(1);
	// 	return ;
	// }
	*pokets = allocat_pipelines(envp, data);
	finish_redirections(data, pokets);
	redirection_helper(data, *pokets);
}
