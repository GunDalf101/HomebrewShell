/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlektaib <mlektaib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 03:21:46 by mlektaib          #+#    #+#             */
/*   Updated: 2023/04/08 02:11:40 by mlektaib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

int	execute_redirect_out(t_ast *node, t_env **env)
{
	int	open_flags;
	int	file_flags;
	int	file_fd;
	t_ast *last;

	while (node && node->type == ast_redirect_out)
	{
		if (node->u_data.redirect_out.tag  == 1)
		{
			open_flags = O_WRONLY | O_CREAT | O_TRUNC;
			file_flags = 0633;
		}
		else if (node->u_data.redirect_out.tag  == 2)
		{
			open_flags = O_WRONLY | O_CREAT | O_APPEND;
			file_flags = 0633;
		}
		file_fd = open(node->u_data.redirect_out.outfile, open_flags,
				file_flags);
		if (file_fd == -1)
		{
			perror(node->u_data.redirect_out.outfile);
			exit(1);
		}
		last = node;
		node = node->u_data.redirect_out.next;
	}
	dup2(file_fd, STDOUT_FILENO);
	close(file_fd);
	return (execute_commands(last->u_data.redirect_out.cmd, env));
}

int	execute_redirect_in(t_ast *node, t_env **env)
{
	int i = 0;
	i++;
	return (execute_commands(node->u_data.redirect_in.cmd, env));
}