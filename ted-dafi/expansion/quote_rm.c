/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_rm.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ted-dafi <ted-dafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 09:48:12 by ted-dafi          #+#    #+#             */
/*   Updated: 2022/07/31 15:00:04 by ted-dafi         ###   ########.fr       */
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
			data->list->token = replace_oper(data->list->token,
					get_spec(), "\"\'|<>", 1);
		}
		data->list = data->list->next;
	}
	data->list = tmp;
}

char	*get_spec(void)
{
	char	*s;
	int		i;

	s = ft_calloc(7, sizeof(char));
	i = 0;
	while (i < 6)
	{
		s[i] = (i + 1) * -1;
		i++;
	}
	return (s);
}

int	free_str(char *s)
{
	if (s)
		free(s);
	return (0);
}

char	*replace_oper(char *s, char *s1, char *s2, int	flag)
{
	int	i;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i])
	{
		s[i] = decide(s1, s2, s[i], s[i]);
		i++;
	}
	(flag == 1) && free_str(s1);
	(flag == 2) && free_str(s2);
	return (s);
}
