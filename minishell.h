/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msouiyeh <msouiyeh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 10:15:08 by ted-dafi          #+#    #+#             */
/*   Updated: 2022/06/16 15:35:48 by msouiyeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <errno.h>
# include <limits.h>
# include <string.h>
# include <fcntl.h>
# include <sys/stat.h>
# include "global_utils/global_utils.h"
# include <readline/readline.h>
# include <readline/history.h>
# include "ted-dafi/ted_dafi.h"
# include "mohamed/get_next_line/get_next_line.h"
# include "mohamed/mohamed.h"
# define WRITE_END 1
# define READ_END 0
#endif
