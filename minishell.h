/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ted-dafi <ted-dafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 10:15:08 by ted-dafi          #+#    #+#             */
/*   Updated: 2022/06/04 13:41:30 by ted-dafi         ###   ########.fr       */
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

typedef struct s_list
{
    char			*content;
	struct s_list	*previous;
	struct s_list	*next;
}   t_list;

typedef struct	s_tokens
{
	char			*meta_data;
	char			*token;
	struct s_tokens	*previous;
	struct s_tokens	*next;
}	t_tokens;

typedef struct s_data
{
	char		*cmd;
	char		*meta_str;
	t_tokens	*list;
}   t_data;


void		*ft_calloc(size_t count, size_t size);
char		**ft_split(char *s, char c);
int	    	ft_strlen(char *s);
size_t		ft_strlcpy(char *dest, const char *src, size_t size);
int	    	ft_strcmp(char *s1, char *s2);
int     	prompt_display(t_data *data, char **envp);
void		ft_lstadd_back(t_tokens **lst, t_tokens *new);
t_tokens	*ft_lstnew(t_tokens *previous, void *meta, char *token);
t_tokens	*ft_lstlast(t_tokens *lst);
char		*ft_substr(char *s, unsigned int start, size_t len);
t_tokens	*ft_slpit_list(char *s, char *s2, char delimiter);
#endif
