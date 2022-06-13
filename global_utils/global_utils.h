/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global_utils.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msouiyeh <msouiyeh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 12:37:21 by ted-dafi          #+#    #+#             */
/*   Updated: 2022/06/13 18:12:05 by msouiyeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GLOBAL_UTILS_H
# define GLOBAL_UTILS_H
# include <stdlib.h>

int		env_scout(char *str, char *var);
int		ft_strlen(char *s);
char	*ft_strjoin(char *s1, char *s2);
int		ft_strlcpy(char *dest, char *src, int size);
int		ft_strcmp(char *s1, char *s2);
void	*ft_calloc(int count, int size);
char    decide(char *main_str, char *mirror_str, char c);
char	*ft_substr(char *s, int start, int len);
char	*ft_strdup(char *s1);
char	*ft_strchr(char *s, int c);
int		ft_isalnum(int c);
int		ft_isprint(int c);
int		ft_isdigit(int c);
int		ft_isascii(int c);
int		ft_isalpha(int c);

#endif
