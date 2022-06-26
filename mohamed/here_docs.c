/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_docs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msouiyeh <msouiyeh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 15:24:44 by msouiyeh          #+#    #+#             */
/*   Updated: 2022/06/26 14:41:52 by msouiyeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


int	compare(char *str, char *limiter, int flag)
{
	int i;

	i = 0;
	if (str == NULL)
		return (1);
	while (str[i] == limiter[i] || !(limiter[i]))
	{
		if (!(limiter[i]) && str[i] == '\n')
		{
			if (flag)
				free(str);
			return (0);
		}
		i++;
	}
	if (flag)
		free(str);
	return (1);
}

char *here_doc_join(char *s1, char *s2, int flag)
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
	int i;
	char c[2];
	char *final;

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

char	*remove_limiter_q(char *limiter)
{
	int		i;
	char	c[2];
	char	*final;
	char	*meta;

	meta = get_meta(limiter);
	final = ft_strdup("");
	c[1] = 0;
	i = 0;
	while (limiter[i])
	{
		if (meta[i] == 'd' || meta[i] == 's')
			i++;
		else
		{
			c[0] = limiter[i];
			final = here_doc_join(final, c, 0);
			i++;
		}
	}
	free(limiter);
	return (final);
}

char	*dynamic_read(char *limiter, int flag, char **envp)
{
	char 	*str;
	char	*final;
	int		size;

	limiter = remove_limiter_q(limiter);
	size = ft_strlen(limiter);
	str = NULL;
	final = ft_strdup("");
	while (compare(str, limiter, 1))
	{
		write (1, "> ", 2);
		str = get_next_line(0);
		if (str == NULL)
			return (final);
		if (flag != -1 && compare(str, limiter, 0))
		 	str = check_and_expand(str, envp);
		final = ft_strjoin_all(&final, str);
	}
	*(ft_strchr(final, '\0') - (size + 1)) = 0; //the + 1 is for the '\n'
	return (final);
}

void	here_doc(int fd, char *limiter, char **envp)
{
	char 	*final;
	int 	i;

	i = -1;
	while (limiter[++i])
	{
		if (limiter[i] == '\'' || limiter[i] == '\"')
		{
			i = -1;
			break ;
		}
		i++;
	}
	final = dynamic_read(limiter, i, envp);
	write (fd, final, ft_strlen(final));
	if (close (fd) == -1)
		printf("error msg in heredoc to be changed\n");
	free(final);
}

void	change_here_doc(t_tokens *itire, char *path)
{
	free(itire->next->token);
	itire->next->token = ft_strdup(path);
}

int	check_max_here_doc(t_tokens *itire)
{
	int i;
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

void	launch_here_docs(t_data *data, char **envp)
{
	t_tokens	*itire;
	char		*path;
	int			fd;
	int			i;

	i = 0;
	path = ft_strdup("/tmp/here_doc..");
	itire = data->list;
	if (check_max_here_doc(itire))
	{
		printf("error max here_doc is exeeded\n");
		exit(2);
	}
	while (itire)
	{
		if (ft_strchr("r", *(itire->meta_data)) && \
			ft_strlen(itire->meta_data) == 2)
		{
			path[13] = (i / 10) + '0'; 
			path[14] = (i % 10) + '0';
			fd = open(path, O_CREAT | O_WRONLY | O_TRUNC, 0666);
			if (fd == -1)
				printf("here_doc tmp file creation faild\n");
			// printf("token %s ::: meta %s\n", itire->next->token, itire->next->meta_data);
			here_doc (fd, itire->next->token, envp);
			change_here_doc(itire, path);
			i++;
		}
		itire = itire->next;
	}
	free(path);
}