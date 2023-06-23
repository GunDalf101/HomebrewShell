/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlektaib <mlektaib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 21:50:47 by mbennani          #+#    #+#             */
/*   Updated: 2023/06/24 00:23:47 by mlektaib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexing_lexer.h"

int	command_finder(char **tokens, int com_researcher)
{
	while ((tokens[com_researcher + 1] && (tokens[com_researcher][0] == '>' \
				|| tokens[com_researcher][0] == '<')) || (com_researcher > 0 \
			&& tokens[com_researcher + 1] && (tokens[com_researcher \
				- 1][0] == '>' || tokens[com_researcher - 1][0] == '<')))
		com_researcher++;
	return (com_researcher);
}

// this function parses the command and redirecion chunks

t_ast	*parse_com_red(char **tokens, t_ast **astable, int *i, int *ascnt)
{
	int		com_researcher;
	t_ast	*cmd;
	int		head_red;

	com_researcher = *i;
	head_red = FALSE;
	cmd = NULL;
	com_researcher = command_finder(tokens, com_researcher);
	if (tokens[com_researcher] && tokens[com_researcher][0] != '|' \
		&& tokens[com_researcher][0] != '(' && tokens[com_researcher][0] != '&' \
		&& tokens[com_researcher][0] != ')')
	{
		astable[*ascnt] = order_command(tokens, &com_researcher);
		cmd = astable[*ascnt];
	}
	while (tokens[*i] && tokens[*i][0] != '|' && tokens[*i][0] != '(' \
		&& tokens[*i][0] != '&' && tokens[*i][0] != ')')
	{
		if (astable[*ascnt])
			*ascnt = *ascnt + 1;
		astable[*ascnt] = order_redirection(cmd, tokens, i, &head_red);
		if (!astable[*ascnt])
			*ascnt = *ascnt - 1;
	}
	return (NULL);
}

// let's now create the nodes

t_ast	*cre_node(char **tokens, t_ast **astable, int *i, int *ascnt)
{
	if (strcmp(tokens[*i], "|") == 0)
	{
		*i = *i + 1;
		astable[*ascnt] = add_new_operation(ast_pipe, NULL, NULL);
	}
	else if (strcmp(tokens[*i], "||") == 0)
	{
		*i = *i + 1;
		astable[*ascnt] = add_new_operation(ast_or, NULL, NULL);
	}
	else if (strcmp(tokens[*i], "&&") == 0)
	{
		*i = *i + 1;
		astable[*ascnt] = add_new_operation(ast_and, NULL, NULL);
	}
	else if (tokens[*i][0] == '(')
	{
		astable[*ascnt] = add_new_subshell(NULL, tokens[*i]);
		*i = *i + 1;
	}
	else
		parse_com_red(tokens, astable, i, ascnt);
	return (NULL);
}

// this function is supposed to make up the nodes

t_ast	**lex_luthor(char **tokens)
{
	t_ast	**astable;
	int		i;
	int		ascnt;

	astable = NULL;
	i = 0;
	ascnt = 0;
	astable = ft_calloc(size_lol(tokens), sizeof(t_ast *));
	while (tokens[i] && ascnt < (int)size_lol(tokens))
	{
		cre_node(tokens, astable, &i, &ascnt);
		ascnt++;
	}
	astable[ascnt] = NULL;
	free_tokens(tokens, (int)strtablen(tokens));
	return (astable);
}
