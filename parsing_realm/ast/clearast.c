/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clearast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbennani <mbennani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 15:45:24 by mlektaib          #+#    #+#             */
/*   Updated: 2023/06/20 11:57:23 by mbennani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

void	free_cmd_node(t_ast *node)
{
	int	i;

	i = 0;
	free(node->u_data.cmd.cmd);
	while (node->u_data.cmd.args[i] && i < node->u_data.cmd.arg_count)
	{
		free(node->u_data.cmd.args[i]);
		i++;
	}
	free(node->u_data.cmd.args);
	free(node);
}

void	free_redirect_out_node(t_ast *node)
{
	free(node->u_data.redirect_out.outfile);
	free_ast_node(node->u_data.redirect_out.cmd);
	free_ast_node(node->u_data.redirect_out.next);
	free(node);
}

void	free_redirect_in_node(t_ast *node)
{
	free(node->u_data.redirect_in.infile);
	free_ast_node(node->u_data.redirect_in.cmd);
	free_ast_node(node->u_data.redirect_in.next);
	free(node);
}

// void	free_heredoc_node(t_ast *node)
// {
// 	free(node->u_data.heredoc.delim);
// 	free_ast_node(node->u_data.heredoc.cmd);
// 	free_ast_node(node->u_data.heredoc.next);
// 	unlink(node->u_data.heredoc.tmp);
// 	free(node->u_data.heredoc.tmp);
// 	free(node);
// }

void free_heredoc_node(t_ast *node)
{
    if (node->u_data.heredoc.delim != NULL)
		free(node->u_data.heredoc.delim);
	free_ast_node(node->u_data.heredoc.cmd);
    free_ast_node(node->u_data.heredoc.next);

    if (node->u_data.heredoc.tmp != NULL)
		unlink(node->u_data.heredoc.tmp);

    free(node);
}

void	free_ast_node(t_ast *node)
{
	if (node == NULL)
		return ;
	if (node->type == ast_cmd || node->type == ast_imp)
		free_cmd_node(node);
	else if (node->type == ast_pipe || node->type == ast_and
		|| node->type == ast_or)
	{
		free_ast_node(node->u_data.operation.left);
		free_ast_node(node->u_data.operation.right);
		free(node);
	}
	else if (node->type == ast_redirect_out)
		free_redirect_out_node(node);
	else if (node->type == ast_redirect_in)
		free_redirect_in_node(node);
	else if (node->type == ast_heredoc)
		free_heredoc_node(node);
	else if (node->type == ast_subshell)
	{
		free_ast_node(node->u_data.subshell.child);
		free(node);
	}
}
