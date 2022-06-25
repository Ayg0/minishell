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

void	fill_redirections(t_pokets	*pokets, char **envp, t_data *data)
{
	pokets = allocat_pipelines(envp, data);
}