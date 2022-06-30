/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msouiyeh <msouiyeh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 10:14:16 by ted-dafi          #+#    #+#             */
/*   Updated: 2022/06/30 05:47:32 by msouiyeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ted_dafi.h"

char	get_meta_quotes(char c, int *s_quoted, int *quoted)
{
	if (c == '"' && *s_quoted == 0)
	{
		*quoted = !(*quoted);
		return ('d');
	}
	else if (c == '\'' && *quoted == 0)
	{
		*s_quoted = !(*s_quoted);
		return ('s');
	}
	return (0);
}

char	*get_meta(char *s)
{
	char	*s_se;
	int		i[2];
	int		quoted;
	int		s_quoted;

	if (!s)
		return (NULL);
	s_se = ft_calloc(ft_strlen(s) + 1, sizeof(char));
	i[0] = 0;
	quoted = 0;
	s_quoted = 0;
	while (s[i[0]])
	{
		i[1] = get_meta_quotes(s[i[0]], &quoted, &s_quoted);
		if (i[1])
			s_se[i[0]] = i[1];
		else if (quoted || s_quoted)
			s_se[i[0]] = 'q';
		else
			s_se[i[0]] = decide(" \t\n|<>", "bbbprw", s[i[0]]);
		i[0]++;
	}
	return (s_se);
}

void	proccess_data(t_data *data)
{
	data->meta_str = get_meta(data->cmd);
	data->list = ft_split_list(data->meta_str, data->cmd, 'b');
}

void	free_triple_pp(char ***envpd)
{
	char	**tmp;

	if (!envpd)
		return ;
	tmp = *envpd;
	while (*envpd && **envpd)
	{
		free(**envpd);
		(*envpd)++;
	}
	free (tmp);
	free(envpd);
}

void	clear_data(t_data *data, t_pokets **pokets, char	***envpd)
{
	void	*tmp;
	char	*var;

	if (data->cmd)
		free(data->cmd);
	data->cmd = NULL;
	if (data->meta_str)
		free(data->meta_str);
	data->meta_str = NULL;
	var = get_variable();
	if (var)
		free(var);
	free_triple_pp(envpd);
	while (data->list)
	{
		free(data->list->meta_data);
		free(data->list->token);
		tmp = data->list;
		data->list = data->list->next;
		free(tmp);
	}
	clean_big_one(*pokets);
	*pokets = NULL;
}

int	ft_count(char **s, char *new)
{
	int	i;

	i = 0;
	while (s && s[i])
		i++;
	if (new)
		i++;
	return (i);
}

char **re_envp(char **envp, char *new)
{
	int		i;
	char	**final;

	i = ft_count(envp, new);
	final = ft_calloc(i + 1, sizeof(char *));
	i = 0;
	while (envp && envp[i])
	{
		final[i] = ft_strdup(envp[i]);
		i++;
	}
	if (new)
		final[i] = new;
	return(final);
}

void	handle_sigint(int signum)
{
	(void)signum;
	write (1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	set_signal_handlers()
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}

int	prompt_display(t_data *data, char **envp)
{
	t_pokets	*pokets;
	int			i;
	char		***envpd;

	pokets = NULL;
	envpd = ft_calloc(sizeof(char **), 1);
	*envpd = re_envp(envp, NULL);
	set_exit_code(0);
	set_signal_handlers();
	i = 0;
	while (1)
	{
		//system("leaks minishell");	
		// int i;
		// t_pokets	*tmp;
		// t_redirect	*tmp2;
		// tmp = pokets;
		// while (tmp)
		// {
		// 	printf("**************pip redirections***********\n");
		// 	printf("--------------read redirections-------------------\n");
		// 	tmp2 = tmp->redirects->read;
		// 	while (tmp2)
		// 	{
		// 		printf("%s----%c\n", tmp2->file_name, tmp2->type);
		// 		tmp2 = tmp2->next;
		// 	}
		// 	printf("---------------write redirections-----------------\n");
		// 	tmp2 = tmp->redirects->write;
		// 	while (tmp2)
		// 	{
		// 		printf("%s----%c\n", tmp2->file_name, tmp2->type);
		// 		tmp2 = tmp2->next;
		// 	}
		// 	printf("---------------argv-----------------\n");
		// 	i = 0;
		// 	while (tmp->av && tmp->av[i])
		// 	{
		// 		printf("%s\n", tmp->av[i]);
		// 		i++;
		// 	}
		// 	tmp = tmp->next;
		// }
		clear_data(data, &pokets, NULL);
		global_initializer();
		data->cmd = readline("\033[0;34mhalf-bash-3.2$\033[0;37m ");
		if (data->cmd == NULL)
		{
			ft_putendl_fd("exit", 1);	
			exit(0);
		}
		if (*(data->cmd) == '\0')
			continue ;
		add_history(data->cmd);
		proccess_data(data);
		if (manage_errors(data) == 0)
			continue ;
		launch_here_docs(data, *envpd);
		if (get_exit_code() != 0)
			continue ;
		expand_all(data, envp);
		fill_redirections(&pokets, envpd, data);
		if (get_exit_code() != 0)
			continue ;
		execute_pipline(pokets);
		if (get_exit_code() != 0)
			continue ;
	}
	return (0);
}
