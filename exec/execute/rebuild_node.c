/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rebuild_node.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlektaib <mlektaib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 19:38:39 by mlektaib          #+#    #+#             */
/*   Updated: 2023/06/23 20:29:38 by mlektaib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
# include "../../parsing_realm/parsing101.h"

t_ast *rebuild_node(t_ast *node)
{
    if (!node)
        return (NULL);
    int len = 0;
    char *newinput;
    int  i = 0;
    printf("cmd = %s, arg[0] === %s \n",node->u_data.cmd.cmd,node->u_data.cmd.args[0]);
    while(node->u_data.cmd.args[i])
    {
        len += ft_strlen(node->u_data.cmd.args[i]);
        i++;
    }
    newinput = malloc(sizeof(char) * len +1+(i-1));
    i = 0;
    int j = 0;
    int l = 0;
    while(node->u_data.cmd.args[i])
    {
        j=0;
        while(node->u_data.cmd.args[i][j])
        {
            newinput[l] = node->u_data.cmd.args[i][j];
            j++;
            l++;
        }
        newinput[l] = ' ';
        l++;
        i++;
    }
    printf("l == %d \n",l);
    newinput[l] = 0;
    printf("newinput = %s \n",newinput);
    // free_cmd_node(node);
    return(parsinginit(newinput));
}