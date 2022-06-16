/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expan.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ted-dafi <ted-dafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 10:52:56 by ted-dafi          #+#    #+#             */
/*   Updated: 2022/06/16 09:49:40 by ted-dafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ted_dafi.h"

char	*check_if_empty(char *s)
{
	if (s && ft_strlen(s))
		return (s);
	free(s);
	return (NULL);
}

int	check_validation(char c, int flag)
{
	return (((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')
			|| c == '_' || ((c >= '0' && c <= '9') * flag)));
}

int	get_and_join(int *i, t_tokens *list, char **str, char **envp)
{
	int	j;

	(*i)++;
	j = *i;
	while (list->token[*i] && check_validation(list->token[*i], 1))
		(*i)++;
	*str = re_join(*str, get_exp(ft_substr(list->token, j, (*i) - j), envp));
	return (0);
}

char	*expand(t_tokens *list, char **envp)
{
	int		i;
	int		flag[2];
	char	*str;

	i = 0;
	flag[0] = 0;
	flag[1] = 0;
	str = NULL;
	while (list->token[i])
	{
		if (list->meta_data[i] == 'd' && !flag[1])
			flag[0] = !flag[0];
		else if (list->meta_data[i] == 's' && !flag[0])
			flag[1] = !flag[1];
		if (list->token[i] == '$' && !flag[1]
			&& check_validation(list->token[i + 1], 0))
			get_and_join(&i, list, &str, envp);
		else
			str = re_join(str, ft_substr(list->token, i++, 1));
	}
	return (check_if_empty(str));
}

int	expand_all(t_data *data, char **envp)
{
	char		*tmp;
	t_tokens	*tmp2;

	tmp2 = data->list;
	while (data->list)
	{
		if (data->list->token)
		{
			tmp = data->list->token;
			data->list->token = expand(data->list, envp);
			if (tmp)
				free(tmp);
			tmp = data->list->meta_data;
			data->list->meta_data = get_meta(data->list->token);
			if (tmp)
				free(tmp);
		}
		data->list = data->list->next;
	}
	data->list = tmp2;
	remove_quotes(data);
	return (0);
}
