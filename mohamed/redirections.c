#include "mohamed.h"

t_pokets	*allocat_pipelines(char **envp, t_data *data)
{
	t_tokens	*itire;
	t_pokets	*final;
	t_pokets	*tmp;
	int 		i;

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
	{
		tmp = ft_new_poket(envp);
		if (tmp == NULL)
		{
			printf("malloc faild\n");
			return (NULL);
		}
		ft_poketadd_back(&final, tmp);
	}
	return (final);
}

char	*mft_strdup(char *str)
{
	if (!str)
		return (NULL);
	return (ft_strdup(str));
}

void	read_redirect(t_tokens *itire, t_pokets *poket)
{
	t_read	*read;

	if (poket->redirects->read)
	{
		read = poket->redirects->read;
		while (read)
			read = read->next;
	}
	read->next = (t_read *)malloc(sizeof(t_read));
	read->next->file_name = mft_strdup(itire->next->token);
	read->next->type = ((ft_strlen(itire->token) == 2) * 'h') +\
									((ft_strlen(itire->token) == 1) * 'f');
	printf("%s-----%c\n", read->next->file_name, read->next->type);
}

void	write_redirect(t_tokens *itire, t_pokets *poket)
{
	t_write	*write;

	if (poket->redirects->write)
	{
		write = poket->redirects->write;
		while (write)
			write = write->next;
	}
	write->next = (t_write *)malloc(sizeof(t_write));
	write->next->file_name = mft_strdup(itire->next->token);
	write->next->code = ((ft_strlen(itire->token) == 2) * O_APPEND) +\
									((ft_strlen(itire->token) == 1) * O_TRUNC);
}

void	process_redirect(t_tokens *itire, t_pokets *poket)
{
	if (*(itire->meta_data) == 'r')
		read_redirect(itire, poket);
	else if (*(itire->meta_data) == 'w')
		write_redirect(itire, poket);
}

void	finish_redirections(t_data *data, t_pokets *pokets)
{
	t_tokens	*itire;
	t_pokets	*poket;

	poket = pokets;
	itire = data->list;
	while (itire)
	{
		if (*(itire->meta_data) == 'r' || *(itire->meta_data) == 'w')
		{
			process_redirect(itire, poket);
			itire = itire->next;
		}
		else if (*(itire->meta_data) == 'p')
			poket = poket->next;
		else
		{
			process_av(&itire, poket);
		}
		itire = itire->next;
	}
}

void	fill_redirections(t_pokets	*pokets, char **envp, t_data *data)
{
	pokets = allocat_pipelines(envp, data);
	finish_rdirections(data, pokets);
}