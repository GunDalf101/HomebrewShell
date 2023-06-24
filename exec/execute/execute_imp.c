/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_imp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbennani <mbennani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 21:20:37 by mlektaib          #+#    #+#             */
/*   Updated: 2023/06/24 10:48:15 by mbennani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

int	execute_imp_commands(t_ast *node, t_env **env, int k)
{
	if (!node)
		return (0);
	if (!ft_strcmp(node->u_data.cmd.cmd, "echo"))
		return (echo(node));
	if (!ft_strcmp(node->u_data.cmd.cmd, "cd"))
		return (cd(node, env));
	if (!ft_strcmp(node->u_data.cmd.cmd, "pwd"))
		return (pwd(env));
	if (!ft_strcmp(node->u_data.cmd.cmd, "export"))
		return (exportadd(env, node));
	if (!ft_strcmp(node->u_data.cmd.cmd, "env"))
		return (envcmd(*env));
	if (!ft_strcmp(node->u_data.cmd.cmd, "unset"))
		return (unsetcmd(env, node));
	if (!ft_strcmp(node->u_data.cmd.cmd, "exit"))
		return (exitcmd(node, k));
	return (0);
}

void	set_imp_commands(t_ast *node)
{
	if (!node)
		return ;
	if (node->type == ast_cmd)
	{
		if (!ft_strcmp(node->u_data.cmd.cmd, "echo")
			|| !ft_strcmp(node->u_data.cmd.cmd, "cd")
			|| !ft_strcmp(node->u_data.cmd.cmd, "pwd")
			|| !ft_strcmp(node->u_data.cmd.cmd, "export")
			|| !ft_strcmp(node->u_data.cmd.cmd, "env")
			|| !ft_strcmp(node->u_data.cmd.cmd, "unset")
			|| !ft_strcmp(node->u_data.cmd.cmd, "exit"))
			node->type = ast_imp;
	}
}
