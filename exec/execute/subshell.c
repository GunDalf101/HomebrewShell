/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlektaib <mlektaib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 03:30:56 by mlektaib          #+#    #+#             */
/*   Updated: 2023/07/13 01:43:14 by mlektaib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

extern t_global	g_global;

int	get_subshell_exit_status(t_ast *node, int pid)
{
	int	status;

	(void)node;
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		return (1);
	return (0);
}

int	execute_subshell(t_ast *node, t_env **env)
{
	return (execute_commands(node->u_data.subshell.child, env, 0));
}
