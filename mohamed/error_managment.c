










//check if the token is wreten correctly, if written false then devide it length by the max consucative acuramces of it and then print from the index of [max acurences * (length / the max consucative acuramces)] 
//if written wright check before or after depending on the type of the operatore 



#include "../minishell.h"

int	find_it(char *token_meta, char *charset)
{
	int i;

	i = 0;
	while (charset[i])
	{
		if (charset[i] == *token_meta)
			return (i);
		i++;
	}
	return (-1);
}

int	check_pip(t_tokens *itire)
{
	if (!itire->next || !itire->previous)
	{
		printf("pip error \n");
		set_exit_code(258);
		return (0);
	}
	else if (ft_strchr("rw", *(itire->previous->meta_data)) != 0 || \
			ft_strlen(itire->meta_data) > 1)
	{
		printf("pip error an operator before \n");
		set_exit_code(258);
		return (0);
	}
	return (1);
}

int	check_redirect(t_tokens *itire)
{
	int	max;
	int	len;

	max = 2;
	len = ft_strlen(itire->meta_data);
	if (!itire->next)
	{
		printf("redirection error missing opperand 1\n");
		set_exit_code(258);
		return (0);
	}
	else if (len > max)
	{
		len = (len - max == 1) + ((len - max > 1) * max);
		printf("redirection error missing opperand near \n");
		write (2, &itire->token[max], len);
		write (2, "\n", 1);
		set_exit_code(258);
		return (0);
	}
	else if (ft_strchr("uqds", *(itire->next->meta_data)) == 0)
	{
		printf("redirection error missing opperand 2\n");
		write (2, itire->next->token, itire->next->max);
		write (2, "\n", 1);
		set_exit_code(258);
		return (0);
	}
	return (1);
}

void	manage_errors(t_data *data)
{
	t_tokens	*itire;
	int			flag;

	itire = data->list;
	flag = 1;
	while(itire && flag)
	{
		// printf("%s\n", itire->token);
		if (*(itire->meta_data) == 'p')
			flag = check_pip(itire);
		else if (ft_strchr("wr", *(itire->meta_data)) != 0)
			flag = check_redirect(itire);
		itire = itire->next;
	}
}