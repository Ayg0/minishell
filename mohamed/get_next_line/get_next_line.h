/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msouiyeh <msouiyeh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 18:26:01 by msouiyeh          #+#    #+#             */
/*   Updated: 2022/06/10 13:14:44 by msouiyeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <unistd.h>
# include <stdlib.h>
# include "../../minishell.h"
# define BUFFER_SIZE 1

char	*free_it(char **target);
char	*handel_the_shit(char **saved);
char	*get_next_line(int fd);
char	*ft_strjoin_all(char **s1, char *s2);

#endif