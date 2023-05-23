/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbennani <mbennani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 01:33:40 by mlektaib          #+#    #+#             */
/*   Updated: 2023/05/23 21:27:50 by mbennani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

t_ast	*add_new_cmd(char *cmd, char **args, int arg_count,
		enum e_ast_type type)
{
	t_ast	*node;
	int		i;

	node = malloc(sizeof(t_ast));
	if (!node)
		return (NULL);
	node->type = type;
	node->u_data.cmd.cmd = ft_strdup(cmd);
	node->u_data.cmd.args = malloc(sizeof(char *) * (arg_count + 1));
	if (!node->u_data.cmd.args)
	{
		free(node->u_data.cmd.cmd);
		free(node);
		return (NULL);
	}
	i = 0;
	while (i < arg_count)
	{
		node->u_data.cmd.args[i] = ft_strdup(args[i]);
		i++;
	}
	node->u_data.cmd.args[arg_count] = NULL;
	node->u_data.cmd.arg_count = arg_count;
	return (node);
}

t_ast	*add_new_subshell(t_ast *child)
{
	t_ast	*node;

	node = malloc(sizeof(t_ast));
	if (!node)
	{
		exit(EXIT_FAILURE);
	}
	node->type = ast_subshell;
	node->u_data.operation.left = child;
	node->u_data.operation.right = NULL;
	return (node);
}

t_ast	*add_new_operation(enum e_ast_type type, t_ast *left, t_ast *right)
{
	t_ast	*node;

	node = malloc(sizeof(t_ast));
	if (!node)
	{
		return (NULL);
	}
	node->type = type;
	node->u_data.operation.left = left;
	node->u_data.operation.right = right;
	return (node);
}

t_ast	*add_new_redirect_out(char *outfile, t_ast *cmd, int tag)
{
	t_ast	*node;

	node = malloc(sizeof(t_ast));
	if (!node)
	{
		return (NULL);
	}
	node->type = ast_redirect_in;
	node->u_data.redirect_out.outfile = outfile;
	node->u_data.redirect_out.cmd = cmd;
	node->u_data.redirect_out.tag = tag;
	return (node);
}

t_ast	*add_new_heredoc(char *delimiter, t_ast *child)
{
	t_ast	*node;

	node = malloc(sizeof(t_ast));
	if (!node)
	{
		return (NULL);
	}
	node->type = ast_heredoc;
	node->u_data.heredoc.delim = delimiter;
	node->u_data.heredoc.cmd = child;
	node->u_data.heredoc.next = NULL;
	return (node);
}

t_ast	*parse_tree(t_ast **lexical_table)
{
	t_ast *root = NULL;
	(void)lexical_table;

	return (root);
}