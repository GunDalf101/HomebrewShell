/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbennani <mbennani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 01:33:40 by mlektaib          #+#    #+#             */
/*   Updated: 2023/06/21 19:26:07 by mbennani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
# include "../parsing101.h"

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
	free(cmd);
	node->u_data.cmd.args = malloc(sizeof(char *) * (arg_count + 1));
	i = 0;
	while (i < arg_count && args[i])
	{
		node->u_data.cmd.args[i] = ft_strdup(args[i]);
		free(args[i]);
		i++;
	}
	free(args);
	node->u_data.cmd.args[i] = NULL;
	node->u_data.cmd.arg_count = arg_count;
	return (node);
}

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

//the function that handles the subshell AKA parenthesis
t_ast	*setting_subshell(t_ast **lexical_table, int counter)
{
	t_ast	*subshell;
	char	*tmp;
	t_ast	*head;
	int		i;

	subshell = lexical_table[counter];
	tmp = subshell->u_data.subshell.reparsethis;
	subshell->u_data.subshell.reparsethis = ft_strtrim(tmp, "( )");
	free(tmp);
	if (subshell->u_data.subshell.reparsethis[0] == '\0')
		return (NULL);
	subshell->u_data.subshell.child = parsinginit(subshell->u_data.subshell.reparsethis);
	counter++;
	i = 0;
	while (lexical_table[counter] && lexical_table[counter]->type != ast_and && lexical_table[counter]->type != ast_or && lexical_table[counter]->type != ast_pipe)
	{
		if (lexical_table[counter]->type == ast_heredoc || lexical_table[counter]->type == ast_redirect_out || lexical_table[counter]->type == ast_redirect_in)
		{
			head = setting_redirection(lexical_table, counter);
			if(head->type == ast_heredoc)
				head->u_data.heredoc.cmd = subshell;
			else if (head->type == ast_redirect_out)
				head->u_data.redirect_out.cmd = subshell;
			else if (head->type == ast_redirect_in)	
				head->u_data.redirect_in.cmd = subshell;
			i++;
			break ;
		}
		counter++;
	}
	if (i == 0)
		return (subshell);
	else
		return (head);
	return(NULL);
}

void	ft_redir_back(t_ast **lst, t_ast *new)
{
	t_ast	*last;
	t_ast	*tmp;

	last = *lst;
	tmp = new;
	if (*lst == NULL)
		*lst = new;
	else
	{
		while (last != NULL)
		{
			tmp = last;
			if (last->type == ast_heredoc)
				last = last->u_data.heredoc.next;
			else if (last->type == ast_redirect_in)
				last = last->u_data.redirect_in.next;
			else if (last->type == ast_redirect_out)
				last = last->u_data.redirect_out.next;
		}
		if (tmp->type == ast_heredoc)
			tmp->u_data.heredoc.next = new;
		else if (tmp->type == ast_redirect_in)
			tmp->u_data.redirect_in.next = new;
		else if (tmp->type == ast_redirect_out)
			tmp->u_data.redirect_out.next= new;
	}
}

t_ast	*setting_redirection(t_ast **lexical_table, int counter)
{
	t_ast *head;
	t_ast *node;
	int i;

	i = counter;
	head = NULL;
	while (lexical_table[counter] && (lexical_table[counter]->type == ast_heredoc || lexical_table[counter]->type == ast_redirect_out || lexical_table[counter]->type == ast_redirect_in))
	{
		node = lexical_table[counter];
		ft_redir_back(&head, node);
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
	t_ast	*right = NULL;

	if (lexical_table[counter + 1]->type == ast_subshell)
		right = setting_subshell(lexical_table, counter + 1);
	else if (lexical_table[counter + 1]->type == ast_cmd || lexical_table[counter + 1]->type == ast_redirect_in || lexical_table[counter + 1]->type == ast_redirect_out || lexical_table[counter + 1]->type == ast_heredoc)
		right = setting_command_redir(lexical_table, counter + 1);
	return (right);
}

// this function is used to set the left side of the tree
t_ast	*setting_west_side(t_ast **lexical_table, int counter)
{
	t_ast	*root = NULL;


	while(lexical_table[counter] && counter >= 0)
	{
		if (lexical_table[counter]->type == ast_pipe || lexical_table[counter]->type == ast_and || lexical_table[counter]->type == ast_or)
		{
			root = lexical_table[counter];
			root->u_data.operation.right = setting_east_side(lexical_table, counter);
			root->u_data.operation.left = setting_west_side(lexical_table, counter - 1);
			break ;
		}
		counter--;
	}
	if (counter == -1)
		root = setting_east_side(lexical_table, counter);
	return (root);
}


//this function gets the root and initiate the growth of the tree
t_ast	*getting_the_root(t_ast **lexical_table, int type, int counter)
{
	t_ast	*root = NULL;
	(void)type;

	while(lexical_table[counter])
		counter++;
	counter--;
	while(lexical_table[counter] && counter >= 0)
	{
		if (lexical_table[counter]->type == ast_pipe || lexical_table[counter]->type == ast_and || lexical_table[counter]->type == ast_or)
		{
			root = lexical_table[counter];
			root->u_data.operation.right = setting_east_side(lexical_table, counter);
			root->u_data.operation.left = setting_west_side(lexical_table, counter - 1);
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
	t_ast *root;

	if (!lexical_table)
		return (NULL);
	root = getting_the_root(lexical_table, 0, 0);
	free(lexical_table);
	return (root);
}
