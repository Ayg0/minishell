/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ted-dafi <ted-dafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 10:15:08 by ted-dafi          #+#    #+#             */
/*   Updated: 2022/05/26 09:29:11 by ted-dafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>

// typedef struct s_token
// {
//     char            *str;
//     // t_metadata        *meda;
//     struct s_token    *next;
//     char            type;
//     char            hasquotes;
// }                    t_token;
// typedef struct s_redirection
// {
//     char                    *left_operand;
//     char                    *right_operand;
//     char                    *file_name;
//     struct s_redirection    *next;
//     int                     type;
//     char                    isroperand_quoted;
// }                            t_redirection;
// typedef struct s_scmd
// {
//     int             pipe[2];
//     char            **args;
//     t_token         *tokens;
//     t_redirection   *redirections;
//     struct s_scmd   *next;
//     struct s_scmd   *previous;
// }                    t_scmd;

void	*ft_calloc(size_t count, size_t size);
char	**ft_split(char *s, char c);
int	    ft_strlen(char *s);
size_t	ft_strlcpy(char *dest, const char *src, size_t size);
int	    ft_strcmp(char *s1, char *s2);
int     prompt_display();
#endif
