/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_managment_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msouiyeh <msouiyeh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 07:55:04 by msouiyeh          #+#    #+#             */
/*   Updated: 2022/07/19 20:17:50 by msouiyeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mohamed.h"

void	error_print(char *error_str, int len)
{
	ft_putstr_fd(ult_strjoin("minishell: syntax error near unexpected token `"\
	, ult_strjoin(ft_substr(error_str, 0, len), "'\n", 1), 2), 2);
	set_exit_code(258);
}
