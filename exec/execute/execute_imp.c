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
	if (strcmp(node->u_data.cmd.cmd, "echo") == 0)
		return (echo(node));
	if (strcmp(node->u_data.cmd.cmd, "cd") == 0)
		return (cd(node, env));
	if (strcmp(node->u_data.cmd.cmd, "pwd") == 0)
		return (pwd());
	if (strcmp(node->u_data.cmd.cmd, "export") == 0)
		return (exportadd(env, node));
	if (strcmp(node->u_data.cmd.cmd, "env") == 0)
		return (envcmd(*env));
	if (strcmp(node->u_data.cmd.cmd, "unset") == 0)
		return (unsetcmd(env, node));
	return (0);
}
