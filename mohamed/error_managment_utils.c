/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_managment_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msouiyeh <msouiyeh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 07:55:04 by msouiyeh          #+#    #+#             */
/*   Updated: 2022/06/30 09:18:53 by msouiyeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mohamed.h"

void	error_print(char *error_str, int len)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	write (2, error_str, len);
	write (2, "'\n", 2);
	set_exit_code(258);
}
