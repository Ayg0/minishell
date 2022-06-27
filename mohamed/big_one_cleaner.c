#include "mohamed.h"

void	clean_big_one(t_pokets *pokets)
{
	int	i;

	i = 0;
	while (pokets)
	{
		while (pokets->av && pokets->av[i])
			free(pokets->av[i++]);
		if (pokets->av)
			free(pokets->av);
		if (pokets->path)
			free(pokets->path);
		
		pokets = pokets->next;
	}
}