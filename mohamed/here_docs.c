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
			free(str);
			return (0);
		}
		i++;
	}
	if (flag)
		free(str);
	return (1);
}

// char *get_env_var()
// { 

// }

char	*check_and_expand(char *str, char **envp)
{
	// char	*final;
	
	// final = ft_strdup("");

	// free(str);
	(void)envp;
	printf("we have to expand here\n");
	return (str);
}

char	*dynamic_read(char *limiter, int flag, char **envp)
{
	char 	*str;
	char	*final;
	int		size;

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
	*(ft_strchr(final, '\0') - (size + 1)) = 0;
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
}

void	change_here_doc(t_tokens *itire, char *path)
{
	free(itire->next->token);
	itire->next->token = ft_strdup(path);
	(itire->meta_data)[1] = 0;
	(itire->token)[1] = 0;
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
			// printf("fd %d ::: %s\n", fd, path);
			here_doc (fd, itire->next->token, envp);
			change_here_doc(itire, path);
			i++;
		}
		itire = itire->next;
	}
	free(path);
}