/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ted-dafi <ted-dafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 10:14:16 by ted-dafi          #+#    #+#             */
/*   Updated: 2022/05/25 10:14:15 by ted-dafi         ###   ########.fr       */
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
        //printf("%s\n", s);
    }
    return (0);
}
