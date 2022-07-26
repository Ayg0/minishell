/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_exp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ted-dafi <ted-dafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 11:20:40 by ted-dafi          #+#    #+#             */
/*   Updated: 2022/07/26 17:10:06 by ted-dafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ted_dafi.h"

static void	put_it(char *dst, char *src, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		dst[i] = src[i];
		i++;
	}
}

char	*ft_strtrim(char *s1, char *set)
{
	size_t		i;
	size_t		up;
	size_t		end;
	char		*p;

	i = 0;
	if (!s1)
		return (NULL);
	end = ft_strlen(s1);
	while (s1[i] && ft_strchr(set, s1[i]))
		i++;
	if (s1[i] == 0)
		return ((char *)ft_calloc(1, 1));
	up = i;
	while (end >= up && ft_strchr(set, s1[end - 1]))
		end--;
	p = (char *)ft_calloc((end - up) + 1, sizeof(char));
	if (p == 0)
		return (0);
	put_it(p, (char *)(s1 + up), end - up);
	return (p);
}

int	check_if_blank(char *s)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = ft_strtrim(s, " \t\n");
	while (tmp[i] || i == 0)
	{
		if (!tmp[i] || tmp[i] == ' ' || tmp[i] == '\t' || tmp[i] == '\n')
		{
			free(tmp);
			return (1);
		}
		i++;
	}
	free (tmp);
	return (0);
}

char	*get_exp(char *var, char c, char **envp)
{
	int		i;
	int		j;
	char	*ret_value;

	ret_value = NULL;
	if (!envp)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		j = env_scout(envp[i], var);
		if (j != -1)
		{
			ret_value = ft_substr(envp[i], j, ft_strlen(envp[i]) - j);
			if (c != 'q' && check_if_blank(ret_value))
				break ;
			free(var);
			return (ret_value);
		}
		i++;
	}
	free(var);
	return (ret_value);
}
