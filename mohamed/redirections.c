/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ted-dafi <ted-dafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 17:42:56 by msouiyeh          #+#    #+#             */
/*   Updated: 2022/06/30 21:46:13 by ted-dafi         ###   ########.fr       */
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

int	ft_wc(char *s, char c)
{
	int	counter;
	int	flag;

	flag = 1;
	counter = 0;
	while (*s)
	{
		while (*s == c)
		{
			s++;
			flag = 1;
		}
		if ((*s != c && flag == 1) && *s)
		{
			counter++;
			flag = 0;
		}
		if (*s)
			s++;
	}
	return (counter + 1);
}

int	is_true_pip(char *str)
{
	int		i;
	char	c;

	c = 0;
	i = 0;
	if (str[0] == 'p')
		c = str[0];
	else
		return (0);
	while (str[i])
	{
		if (str[i] != c)
			return (0);
		i++;
	}
	return (1);
}

void	process_av(t_tokens **itire, t_pokets *poket)
{
	t_tokens	*tmp;
	int			i;

	i = 0;
	tmp = *itire;
	while (tmp && is_true_pip(tmp->meta_data) == 0)
	{
		i += ft_wc(tmp->meta_data, 'b');
		tmp = tmp->next;
	}
	poket->av = (char **)ft_calloc(i + 1, sizeof(char *));
	process_av_help(itire, poket);
	if (*itire && is_true_pip((*itire)->meta_data))
		*itire = (*itire)->previous;
}

void	redirection_helper(t_data	*data, t_pokets	*poket)
{
	t_tokens	*itire;

	itire = data->list;
	while (itire)
	{
		if (is_true_pip(itire->meta_data))
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
	//resplit_tokens(data);
	// while (data->list)
	// {
	// 	printf("%s    %s\n", data->list->token, data->list->meta_data);
	// 	data->list = data->list->next;
	// }
	*pokets = allocat_pipelines(envp, data);
	finish_redirections(data, pokets);
	redirection_helper(data, *pokets);
}
