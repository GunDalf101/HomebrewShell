/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expansion.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlektaib <mlektaib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 23:02:19 by mlektaib          #+#    #+#             */
/*   Updated: 2023/06/21 23:02:20 by mlektaib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "execute.h"

extern t_global g_global;

char    *heredoc_expansion(char *str,t_env *env)
{
    t_expand expand;

    expand_intialize(&expand, str);
    while(expand.str[expand.i])
    {
        if(str[expand.i] == '$')
            expand_start(&expand,env);
        expand.i++;
    }
    return (expand.str);
}

char	*quotes_remover(char *str) 
{
    int len = strlen(str);
    int i;
	int j;
    int inside_single = FALSE;
	int	inside_double = FALSE;
    int s = 0;
    while(str[s] && str[s] != '\'' && str[s] == '\"')
        s++;
    if (!str[s])
        return (str);
    for (i = j = 0; i < len; i++) {
        if (str[i] == '\'' && !inside_double) {
            inside_single = !inside_single;
        } else if (str[i] == '"' && !inside_single) {
            inside_double = !inside_double;
        } else {
            str[j++] = str[i];
        }
    }
    str[j] = '\0';
	return (str);
}



void replace_env(t_expand *expand)
{
    char *firstpart;
    char *secondpart;
    char *new_str;

    firstpart = ft_substr(expand->str, 0, expand->start);
    secondpart = ft_substr(expand->str, expand->end, expand->len - expand->end);
    new_str = ft_strjoin(firstpart, expand->value);
    free(firstpart);
    free(expand->str);
    expand->str = ft_strjoin(new_str, secondpart);
    free(secondpart);
    free(new_str);
    expand->len = ft_strlen(expand->str);
    expand->i = expand->start + ft_strlen(expand->value);
    expand->j = expand->i;
}