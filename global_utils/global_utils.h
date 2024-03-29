/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global_utils.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ted-dafi <ted-dafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 12:37:21 by ted-dafi          #+#    #+#             */
/*   Updated: 2022/07/31 14:48:17 by ted-dafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GLOBAL_UTILS_H
# define GLOBAL_UTILS_H
# include <stdlib.h>
# include <unistd.h>

int		ft_strncmp(const	char	*s1, const	char	*s2, size_t	n);
char	**ft_split(char *s, char c);
void	ft_putchar_fd(char c, int fd);
int		ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
int		env_scout(char *str, char *var);
int		ft_strlen(char *s);
char	*ft_strjoin(char *s1, char *s2);
int		ft_strlcpy(char *dest, char *src, int size);
int		ft_strcmp(char *s1, char *s2);
void	*ft_calloc(int count, int size);
char	*ft_substr(char *s, int start, int len);
char	*ft_strdup(char *s1);
char	*ft_strchr(char *s, int c);
int		ft_isalnum(int c);
int		ft_isprint(int c);
int		ft_isdigit(int c);
int		ft_isascii(int c);
int		ft_isalpha(int c);
int		ft_atoi(char *str, int *flag);
char	*ft_itoa(int n);
int		put_history(void);
char	decide(char *main_str, char *mirror_str, char c, char def);
#endif
