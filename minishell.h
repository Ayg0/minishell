/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msouiyeh <msouiyeh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 10:15:08 by ted-dafi          #+#    #+#             */
/*   Updated: 2022/07/26 22:57:08 by msouiyeh         ###   ########.fr       */
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
# include <termios.h>
# include "global_utils/global_utils.h"
# include <readline/readline.h>
# include <readline/history.h>
# include "ted-dafi/ted_dafi.h"
# include "mohamed/mohamed.h"
# define WRITE_END 1
# define READ_END 0
#endif
