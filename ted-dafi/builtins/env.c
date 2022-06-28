/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ted-dafi <ted-dafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 12:12:35 by ted-dafi          #+#    #+#             */
/*   Updated: 2022/06/28 14:18:40 by ted-dafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ted_dafi.h"

int	main(int ac, char **av, char **envp)
{
	while (envp && *envp)
	{
		write(1, *envp, ft_strlen(*envp));
		write(1, "\n", 1);
		envp++;
	}
}