/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_rm.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msouiyeh <msouiyeh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 09:48:12 by ted-dafi          #+#    #+#             */
/*   Updated: 2022/06/28 20:59:21 by msouiyeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ted_dafi.h"

int	count_q(char *s)
{
	int	i;
	int	total;

	i = 0;
	total = 0;
	while (s[i])
	{
		if (s[i] == 'd' || s[i] == 's')
			total++;
		i++;
	}
	return (total);
}

void	make_new(t_tokens *list, int total_q)
{
	char	*token;
	char	*meta;
	int		i;
	int		j;

	i = 0;
	j = 0;
	token = ft_calloc(sizeof(char), (ft_strlen(list->token) - total_q + 1));
	meta = ft_calloc(sizeof(char), (ft_strlen(list->token) - total_q + 1));
	while (list->meta_data[i])
	{
		if (list->meta_data[i] != 'd' && list->meta_data[i] != 's')
		{
			token[j] = list->token[i];
			meta[j] = list->meta_data[i];
			j++;
		}
		i++;
	}
	free(list->meta_data);
	free(list->token);
	list->meta_data = meta;
	list->token = token;
}

void	remove_quotes(t_data *data)
{
	int			total_q;
	t_tokens	*tmp;

	tmp = data->list;
	while (data->list)
	{
		if (data->list->token)
		{
			total_q = count_q(data->list->meta_data);
			make_new(data->list, total_q);
		}
			data->list = data->list->next;
	}
	data->list = tmp;
}
