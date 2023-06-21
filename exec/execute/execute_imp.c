/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_imp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlektaib <mlektaib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 21:20:37 by mlektaib          #+#    #+#             */
/*   Updated: 2023/04/09 06:03:09 by mlektaib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

int	execute_imp_commands(t_ast *node, t_env **env)
{
	if(!node)
		return (0);
	if (!strcmp(node->u_data.cmd.cmd, "echo"))
		return (echo(node));
	if (!strcmp(node->u_data.cmd.cmd, "cd"))
		return (cd(node, env));
	if (!strcmp(node->u_data.cmd.cmd, "pwd"))
		return (pwd(env));
	if (!strcmp(node->u_data.cmd.cmd, "export"))
		return (exportadd(env, node));
	if (!strcmp(node->u_data.cmd.cmd, "env"))
		return (envcmd(*env));
	if (!strcmp(node->u_data.cmd.cmd, "unset"))
		return (unsetcmd(env, node));
	if (!strcmp(node->u_data.cmd.cmd, "exit"))
		return (exitcmd(node));
	return (0);
}

void set_imp_commands(t_ast *node)
{
	if(!node)
		return ;
	if (node->type == ast_cmd)
	{
		if (!strcmp(node->u_data.cmd.cmd, "echo") || !strcmp(node->u_data.cmd.cmd, "cd") || !strcmp(node->u_data.cmd.cmd, "pwd") || !strcmp(node->u_data.cmd.cmd, "export") || !strcmp(node->u_data.cmd.cmd, "env") || !strcmp(node->u_data.cmd.cmd, "unset")|| !strcmp(node->u_data.cmd.cmd, "exit"))
			node->type = ast_imp;
	}
}
