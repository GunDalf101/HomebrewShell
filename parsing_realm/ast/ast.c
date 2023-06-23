/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlektaib <mlektaib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 01:33:40 by mlektaib          #+#    #+#             */
/*   Updated: 2023/06/24 00:23:14 by mlektaib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing101.h"
#include "ast.h"

t_ast	*add_new_subshell(t_ast *child, char *reparsethis)
{
	t_ast	*node;

	node = malloc(sizeof(t_ast));
	if (!node)
		exit(EXIT_FAILURE);
	node->type = ast_subshell;
	node->u_data.subshell.reparsethis = ft_strdup(reparsethis);
	node->u_data.subshell.child = child;
	return (node);
}

t_ast	*add_new_operation(enum e_ast_type type, t_ast *left, t_ast *right)
{
	t_ast	*node;

	node = malloc(sizeof(t_ast));
	if (!node)
		return (NULL);
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
		return (NULL);
	node->type = ast_redirect_out;
	node->u_data.redirect_out.outfile = outfile;
	node->u_data.redirect_out.cmd = cmd;
	node->u_data.redirect_out.tag = tag;
	node->u_data.redirect_out.next = NULL;
	return (node);
}

t_ast	*add_new_redirect_in(char *infile, t_ast *cmd)
{
	t_ast	*node;

	node = malloc(sizeof(t_ast));
	if (!node)
		return (NULL);
	node->type = ast_redirect_in;
	node->u_data.redirect_in.infile = infile;
	node->u_data.redirect_in.cmd = cmd;
	node->u_data.redirect_in.next = NULL;
	return (node);
}

t_ast	*add_new_heredoc(char *delimiter, t_ast *child)
{
	t_ast	*node;

	node = malloc(sizeof(t_ast));
	if (!node)
		return (NULL);
	node->type = ast_heredoc;
	node->u_data.heredoc.delim = delimiter;
	node->u_data.heredoc.cmd = child;
	node->u_data.heredoc.next = NULL;
	return (node);
}
