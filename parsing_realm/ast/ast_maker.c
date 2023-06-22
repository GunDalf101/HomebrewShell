/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_maker.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbennani <mbennani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 02:39:55 by mbennani          #+#    #+#             */
/*   Updated: 2023/06/22 04:42:46 by mbennani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing101.h"
#include "ast.h"

// growing commands n shit

t_ast	*setting_command_redir(t_ast **lexical_table, int counter)
{
	t_ast	*head;
	int		i;

	i = 0;
	while (lexical_table[counter] && lexical_table[counter]->type != ast_and
		&& lexical_table[counter]->type != ast_or
		&& lexical_table[counter]->type != ast_pipe)
	{
		if (lexical_table[counter]->type == ast_heredoc
			|| lexical_table[counter]->type == ast_redirect_out
			|| lexical_table[counter]->type == ast_redirect_in)
		{
			head = setting_redirection(lexical_table, counter);
			i++;
			break ;
		}
		counter++;
	}
	if (i == 0)
	{
		counter--;
		head = lexical_table[counter];
	}
	return (head);
}

// this function is used to set the right side of the tree
t_ast	*setting_east_side(t_ast **lexical_table, int counter)
{
	t_ast	*right;

	right = NULL;
	if (lexical_table[counter + 1]->type == ast_subshell)
		right = setting_subshell(lexical_table, counter + 1);
	else if (lexical_table[counter + 1]->type == ast_cmd
		|| lexical_table[counter + 1]->type == ast_redirect_in
		|| lexical_table[counter + 1]->type == ast_redirect_out
		|| lexical_table[counter + 1]->type == ast_heredoc)
		right = setting_command_redir(lexical_table, counter + 1);
	return (right);
}

// this function is used to set the left side of the tree
t_ast	*setting_west_side(t_ast **lexical_table, int counter)
{
	t_ast	*root;

	root = NULL;
	while (lexical_table[counter] && counter >= 0)
	{
		if (lexical_table[counter]->type == ast_pipe
			|| lexical_table[counter]->type == ast_and
			|| lexical_table[counter]->type == ast_or)
		{
			root = lexical_table[counter];
			root->u_data.operation.right = setting_east_side(lexical_table, \
				counter);
			root->u_data.operation.left = setting_west_side(lexical_table, \
				counter - 1);
			break ;
		}
		counter--;
	}
	if (counter == -1)
		root = setting_east_side(lexical_table, counter);
	return (root);
}

// this function gets the root and initiate the growth of the tree
t_ast	*getting_the_root(t_ast **lexical_table, int type, int counter)
{
	t_ast	*root;

	root = NULL;
	(void)type;
	while (lexical_table[counter])
		counter++;
	counter--;
	while (lexical_table[counter] && counter >= 0)
	{
		if (lexical_table[counter]->type == ast_pipe
			|| lexical_table[counter]->type == ast_and
			|| lexical_table[counter]->type == ast_or)
		{
			root = lexical_table[counter];
			root->u_data.operation.right = setting_east_side(lexical_table, \
				counter);
			root->u_data.operation.left = setting_west_side(lexical_table, \
				counter - 1);
			break ;
		}
		counter--;
	}
	if (counter == -1)
		root = setting_east_side(lexical_table, counter);
	return (root);
}

// let's grow the tree
t_ast	*parse_tree(t_ast **lexical_table)
{
	t_ast	*root;

	if (!lexical_table)
		return (NULL);
	root = getting_the_root(lexical_table, 0, 0);
	free(lexical_table);
	return (root);
}
