/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ted-dafi <ted-dafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 10:14:16 by ted-dafi          #+#    #+#             */
/*   Updated: 2022/05/26 09:38:26 by ted-dafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

// int prompt_display(char **env)
// {
//     int i;
//     char **o;

//     o = malloc(sizeof(char*) * 4);
//     o[0] = "bash";
//     o[1] = "-c";
//     o[3] = '\0';
//     write(1, "\e[H\e[2J", 8);
//     while(1)
//     {
//         write(1, "half-bash-3.2$ ", 16);
//         char    s[1000000] = {};
//         i = 0;
//         while (i == 0 || s[i - 1] != '\n'){
//             read(1, &s[i], 1);i++;}
//         o[2] = s;
//         if (!fork())
//             execve("/bin/bash", o, env);
//         wait(NULL);
//     }
//     return (0);
// }

char    *get_meta(char *s)
{
    char    *s_se;
    int i;

    i = ft_strlen(s);
    s_se = ft_calloc(i, sizeof(char));
    i = 0;
    while (s[i])
    {
        while (i == 0 || (s[i] && s[i - 1] != '"' && s[i - 1] != '\''))
        {
            if (s[i] == ' ')
                s_se[i] = 's';
            else
               s_se[i] = 'u';
            i++;
        }
        while (s[i] && s[i] != '"' && s[i] != '\'')
            s_se[i++] = 'q';     
    }
    return (s_se);
}

int parsing(char *s)
{
    /*
        echo "wow\nok" | grep "ok"
        uuuusuqqqususuuuusuqqu
        echo
        "wow\nok"
        |
        grep
        "ok"
    */
   char *ss;
   ss = get_meta(s);
   printf("%s\n", ss);
   return (0);
}

int prompt_display()
{
    int     i;
    char    *s = NULL;

    write(1, "\e[H\e[2J", 8);
    i = 0;
    while(ft_strcmp(s, "exit"))
    {
        s = readline("half-bash-3.2$ ");
        add_history(s);
        parsing(s);
        free (s);
    }
    return (0);
}
