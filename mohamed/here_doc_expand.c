/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_expand.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msouiyeh <msouiyeh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 01:46:54 by msouiyeh          #+#    #+#             */
/*   Updated: 2022/06/28 02:04:10 by msouiyeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mohamed.h"

char	*here_doc_join(char *s1, char *s2, int flag)
{
	char	*final;

	if (!s1 || !s2)
		return (NULL);
	final = ft_strjoin(s1, s2);
	free (s1);
	if (flag)
		free(s2);
	return (final);
}

int	check_name(char	*name, int *i)
{
	while (name[*i] == '_' || ft_isalnum(name[*i]))
		(*i)++;
	return (*i);
}

char	*final_expand(char *str, int *i, char **envp)
{
	char	*tmp;
	char	*final;
	int		s;

	s = *i;
	tmp = ft_substr(str, s, check_name(str, i) - s);
	final = ft_strdup("");
	while (*envp)
	{
		if (env_scout(*envp, tmp) != -1)
		{
			free(final);
			final = ft_substr(*envp, env_scout(*envp, tmp), ft_strlen(*envp));
			break ;
		}
		envp++;
	}
	free(tmp);
	return (final);
}

char	*check_and_expand(char *str, char **envp)
{
	int		i;
	char	c[2];
	char	*final;

	final = ft_strdup("");
	c[1] = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && (str[i + 1] == '_' || ft_isalpha(str[i + 1])))
		{
			i++;
			final = here_doc_join(final, final_expand(str, &i, envp), 1);
		}
		else
		{
			c[0] = str[i];
			final = here_doc_join(final, c, 0);
			i++;
		}
	}
	free(str);
	return (final);
}

int	check_max_here_doc(t_tokens *itire)
{
	int	i;

	i = 0;
	while (itire)
	{
		if (ft_strchr("r", *(itire->meta_data)) && \
			ft_strlen(itire->meta_data) == 2)
			i++;
		itire = itire->next;
	}
	if (i > 16)
		return (1);
	else
		return (0);
}
