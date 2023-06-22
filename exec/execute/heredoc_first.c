/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_first.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlektaib <mlektaib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 16:27:09 by mlektaib          #+#    #+#             */
/*   Updated: 2023/06/22 17:17:43 by mlektaib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

extern t_global g_global;

t_ast   *init_heredoc(t_fd *fd, t_ast *node, t_env **env)
{
    t_ast   *cmd;

    cmd = NULL;
	fd->error = 0;
	fd->infile_fd = 0;
	fd->outfile_fd = 1;
    cmd = get_cmd_node(node);
    if (cmd && cmd->type == ast_subshell)
        execute_all_heredocs(node->u_data.subshell.child, env);
    return (cmd);
}

t_ast   *get_next_node(t_ast *node)
{
    if (node->type == ast_redirect_out)
        return (node->u_data.redirect_in.cmd);
    else if(node->type == ast_redirect_in)
        return (node->u_data.redirect_in.next);
    return (node);
}

char *generate_tmp_name()
{
    char *tmp;
    char *name;
    tmp = ft_itoa(generate_rand());
    name = ft_strjoin("/tmp/.heredoc", tmp);
    free(tmp);
    return (name);
}


int	execute_heredocs(t_ast *node, t_env **env)
{
	t_fd	fd;
	t_ast	*cmd;

	cmd = NULL;
    cmd = init_heredoc(&fd,node,env);
	while (node && g_global.run != 130)
	{
        g_global.run = 0;
		if (node->type == ast_redirect_out || node->type == ast_redirect_in)
			node = get_next_node(node);
		else if (node->type == ast_heredoc)
		{
			node->u_data.heredoc.tmp = generate_tmp_name();
			open_tmp_file(node, &fd);
			node = heredoc_handler(node, &fd,env);
            if (fd.infile_fd != STDIN_FILENO)
                close(fd.infile_fd);
			if (!node || node->type != ast_heredoc)
				continue ;
			node = node->u_data.heredoc.next;
		}
	}
	return (g_global.run);
}

int	execute_all_heredocs(t_ast *node, t_env **env)
{
	if (!node)
		return (0);
	else if (node->type == ast_pipe)
	{
		execute_all_heredocs(node->u_data.operation.left, env);
		execute_all_heredocs(node->u_data.operation.right, env);
	}
	else if (node->type == ast_redirect_in || node->type == ast_redirect_out
		|| node->type == ast_heredoc)
		return (execute_heredocs(node, env));
	else if (node->type == ast_subshell)
		return (execute_all_heredocs(node->u_data.subshell.child, env));
	else if (node->type == ast_and)
	{
		execute_all_heredocs(node->u_data.operation.left, env);
		execute_all_heredocs(node->u_data.operation.right, env);
	}
	else if (node->type == ast_or)
	{
		execute_all_heredocs(node->u_data.operation.left, env);
		execute_all_heredocs(node->u_data.operation.right, env);
	}
	return (1);
}
