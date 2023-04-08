/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlektaib <mlektaib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 21:21:28 by mlektaib          #+#    #+#             */
/*   Updated: 2023/04/08 21:21:29 by mlektaib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.h"

int ft_check_n(char *arg)
{
	if(!arg)
		return 0;
	if(arg[0] != '-')
		return 0;
	else
	{
		arg++;
		while(*arg)
		{
			if(*arg != 'n')
				return 0;
			arg++;
		}
		return (1);
	}
	return (1);
}

int echo(t_ast *node)
{
	int flag  = 0;
	int i = 0;

	flag = ft_check_n(node->u_data.cmd.args[1]);
	if(flag == 1)
	{
		i = 2;
		while(node->u_data.cmd.args[i])
		{
			ft_putstr_fd(node->u_data.cmd.args[i],1);
			i++;
			if(i !=node->u_data.cmd.arg_count)
				ft_putstr_fd(" ",1);
		}
	}
	else if(flag == 0)
	{
		i = 1;
		while(node->u_data.cmd.args[i])
		{
			ft_putstr_fd(node->u_data.cmd.args[i],1);
			i++;
			if(i !=node->u_data.cmd.arg_count)
				ft_putstr_fd(" ",1);
		}
		ft_putendl_fd("",1);
	}
	return 0;
}