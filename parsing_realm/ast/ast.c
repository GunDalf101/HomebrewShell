/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbennani <mbennani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 01:33:40 by mlektaib          #+#    #+#             */
/*   Updated: 2023/06/08 14:38:16 by mbennani         ###   ########.fr       */
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
		exit(EXIT_FAILURE);
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

//the function that handles the subshell AKA parenthesis
t_ast	*setting_subshell(t_ast **lexical_table, int counter)
{
	t_ast	*subshell;

	subshell = ft_calloc(sizeof(t_ast), 1);
	subshell = lexical_table[counter];
	subshell->u_data.subshell.child = getting_the_root(lexical_table, 1, counter);
	return (subshell);
}

t_ast	*setting_redirection(t_ast **lexical_table, int counter)
{
	t_ast *head;
	t_ast *node = NULL;

	head = node;
	while (lexical_table[counter] && (lexical_table[counter]->type == ast_heredoc || lexical_table[counter]->type == ast_redirect_out || lexical_table[counter]->type == ast_redirect_in))
	{
		node = ft_calloc(sizeof(t_ast), 1);
		node = lexical_table[counter];
		if (node->type == ast_heredoc)
			node = node->u_data.heredoc.next;
		else if (node->type == ast_redirect_in)
			node = node->u_data.redirect_in.next;
		else if (node->type == ast_redirect_out)
			node = node->u_data.redirect_out.next;
		counter++;
	}
	return (head);
}


// growing commands n shit

t_ast	*setting_command_redir(t_ast **lexical_table, int counter)
{
	t_ast	*head;
	int		i;

	i = 0;
	while (lexical_table[counter] && lexical_table[counter]->type != ast_and && lexical_table[counter]->type != ast_or && lexical_table[counter]->type != ast_pipe)
	{
		if (lexical_table[counter]->type == ast_heredoc || lexical_table[counter]->type == ast_redirect_out || lexical_table[counter]->type == ast_redirect_in)
		{
			head = ft_calloc(sizeof(t_ast), 1);
			head = setting_redirection(lexical_table, counter);
			i++;
			break ;
		}
		counter++;
	}
	if (i == 0)
	{
		counter--;
		head = ft_calloc(sizeof(t_ast), 1);
		head = lexical_table[counter];
	}
	return (head);
}


// this function is used to set the right side of the tree
t_ast	*setting_east_side(t_ast **lexical_table, int counter)
{
	t_ast	*right = NULL;

	if (lexical_table[counter + 1]->type == ast_subshell)
		right = setting_subshell(lexical_table, counter + 1);
	else if (lexical_table[counter + 1]->type == ast_cmd)
		right = setting_command_redir(lexical_table, counter + 1);
	return (right);
}

// this function is used to set the left side of the tree
t_ast	*setting_west_side(t_ast **lexical_table, int counter)
{
	t_ast	*root = NULL;


	while(lexical_table[counter] && counter >= 0)
	{
		// printf ("tbbi lol\n");
		if (lexical_table[counter]->type == ast_pipe || lexical_table[counter]->type == ast_and || lexical_table[counter]->type == ast_or)
		{
			root = ft_calloc(sizeof(t_ast), 1);
			root = lexical_table[counter];
			root->u_data.operation.right = setting_east_side(lexical_table, counter);
			root->u_data.operation.left = setting_west_side(lexical_table, counter - 1);
			break ;
		}
		counter--;
	}
	if (counter == -1)
	{
		root = ft_calloc(sizeof(t_ast), 1);
		root = setting_east_side(lexical_table, counter);
	}
	return (root);
}


//this function gets the root and initiate the growth of the tree
t_ast	*getting_the_root(t_ast **lexical_table, int type, int counter)
{
	t_ast	*root = NULL;

	if (type == 0)
	{
		while(lexical_table[counter])
			counter++;
	}
	else if (type == 1)
	{
		while(lexical_table[counter] && lexical_table[counter]->type != ast_subshell_end)
			counter++;
	}
	counter--;
	while(lexical_table[counter] && counter >= 0)
	{
		if (lexical_table[counter]->type == ast_pipe || lexical_table[counter]->type == ast_and || lexical_table[counter]->type == ast_or)
		{
			root = ft_calloc(sizeof(t_ast), 1);
			root = lexical_table[counter];
			root->u_data.operation.right = setting_east_side(lexical_table, counter);
			root->u_data.operation.left = setting_west_side(lexical_table, counter - 1);
			break ;
		}
		counter--;
	}
	if (counter == -1)
	{
		root = ft_calloc(sizeof(t_ast), 1);
		root = setting_east_side(lexical_table, counter);
	}
	return (root);
}

// let's grow the tree
t_ast	*parse_tree(t_ast **lexical_table)
{
	t_ast *root = NULL;

	root = getting_the_root(lexical_table, 0, 0);
	printf("root = %p\n", root);
	return (root);
}
