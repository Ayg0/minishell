/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ted-dafi <ted-dafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 20:31:20 by ted-dafi          #+#    #+#             */
/*   Updated: 2022/07/22 15:38:23 by ted-dafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include "../ted_dafi.h"
# include <stdlib.h>
# include <unistd.h>

char	*ft_stroin(char **s1, char *s2);
int		ft_newlchr(const char *s);
int		ft_stlen(char *s);
char	*get_next_line(int fd);
char	*my_free(char **buff, char **temp, int flag);
#endif
