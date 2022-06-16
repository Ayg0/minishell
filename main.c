/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ted-dafi <ted-dafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 11:33:31 by ted-dafi          #+#    #+#             */
/*   Updated: 2022/06/16 09:42:06 by ted-dafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **envp)
{
	t_data	*data;

	(void)ac;
	(void)av;
	data = ft_calloc(1, sizeof(t_data));
	prompt_display(data, envp);
	return (0);
}
