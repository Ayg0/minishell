/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expan.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ted-dafi <ted-dafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 10:52:56 by ted-dafi          #+#    #+#             */
/*   Updated: 2022/07/31 13:06:10 by ted-dafi         ###   ########.fr       */
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

int	check_validation(char c, int ex_flag, int num_flag)
{
	return (((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')
			|| c == '_' || ((c == '?') * ex_flag)
			|| ((c >= '0' && c <= '9') * num_flag)));
}

int	get_and_join(int *i, t_tokens *list, char **str, char **envp)
{
	int	j;

	(*i)++;
	j = *i;
	list->flag = 0;
	if (list->token[*i] == '?')
	{
		if (list->index == 0)
			*str = re_join(*str, ft_itoa(get_exit_code()));
		else
			*str = ult_strjoin(*str, "0", 1);
		(*i)++;
	}
	else
	{
		while (list->token[*i] && check_validation(list->token[*i], 0, 1))
			(*i)++;
		if (*i > j)
			*str = re_join(*str,
					replace_oper(get_exp(ft_substr(list->token, j,
								(*i) - j), list->meta_data[j], envp),
						"\"\'|<>", "\222\217\132\196\194"));
		list->flag = -404 * ((*str)[0] == '\0');
	}
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
	str = ft_strdup("");
	while (list->token[i])
	{
		if (list->meta_data[i] == 'd' && !flag[1])
			flag[0] = !flag[0];
		else if (list->meta_data[i] == 's' && !flag[0])
			flag[1] = !flag[1];
		if (list->token[i] == '$' && !flag[1]
			&& check_validation(list->token[i + 1], 1, 0))
			get_and_join(&i, list, &str, envp);
		else if (list->token[i] == '$' && list->token[i] == 'u')
			i++;
		else
			str = re_join(str, ft_substr(list->token, i++, 1));
	}
	return (str);
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
			data->list->old_token = data->list->token;
			data->list->token = expand(data->list, envp);
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
