/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbennani <mbennani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 21:50:47 by mbennani          #+#    #+#             */
/*   Updated: 2023/06/19 16:32:04 by mbennani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexing_lexer.h"

size_t	strtablen(char **tokens)
{
	size_t	cnt;

	cnt = 0;
	while (tokens[cnt])
		cnt++;
	return (cnt);
}


// this is where the output commands are ordered

t_ast	*order_command(char **tokens, int *i)
{
	char	*cmd;
	char	**args;
	int		arg_count = 0;
	int		argcnt;
	int		tempi;

	arg_count = 0;
	argcnt = 0;
	tempi = *i;
	if ((tokens[tempi] && (tokens[tempi][0] == '>' || tokens[tempi][0] == '<')) || (tokens[tempi] && tempi > 0 && (tokens[tempi - 1][0] == '>' || tokens[tempi - 1][0] == '<')))
		return (NULL);
	cmd = ft_strdup(tokens[*i]);
	while (tokens[tempi] && tokens[tempi][0] != '|' && tokens[tempi][0] != '(' && tokens[tempi][0] != '&' && tokens[tempi][0] != ')')
	{
		if ((tokens[tempi] && (tokens[tempi][0] == '>' || tokens[tempi][0] == '<')) || (tokens[tempi] && tempi > 0 && (tokens[tempi - 1][0] == '>' || tokens[tempi - 1][0] == '<')))
			arg_count--;
		arg_count++;
		tempi++;
	}
	args = ft_calloc(arg_count + 1, sizeof(char *));
	while (tokens[*i] && tokens[*i][0] != '|' && tokens[*i][0] != '(' && tokens[*i][0] != '&' && tokens[*i][0] != ')')
	{
		while ((tokens[*i] && (tokens[*i][0] == '>' || tokens[*i][0] == '<')) || (tokens[*i] && *i > 0 && (tokens[*i - 1][0] == '>' || tokens[*i - 1][0] == '<')))
			*i = *i + 1;
		if (!tokens[*i])
			break;
		args[argcnt] = ft_strdup(tokens[*i]);
		*i = *i + 1;
		argcnt++;
	}
	return (add_new_cmd(cmd, args, arg_count, ast_cmd));
}

// this is where output redirections are ordered

t_ast	*order_redirectout(t_ast *cmd,char **tokens, int *i, int *head_red)
{
	char	*outfile;
	int		tag = 0;

	if (strcmp(tokens[*i], ">") == 0)
		tag = 1;
	else if (strcmp(tokens[*i], ">>") == 0)
		tag = 2;
	*i = *i + 1;
	outfile = ft_strdup(tokens[*i]);
	*i = *i + 1;
	if (*head_red == FALSE)
	{
		*head_red = TRUE;	
		return (add_new_redirect_out(outfile, cmd, tag));
	}
	else
		return (add_new_redirect_out(outfile, NULL, tag));
	return (NULL);
}

// this is where input redirections are ordered

t_ast	*order_redirectin(t_ast *cmd,char **tokens, int *i, int *head_red)
{
	char	*infile;

	*i = *i + 1;
	infile = ft_strdup(tokens[*i]);
	*i = *i + 1;
	if (*head_red == FALSE)
	{
		*head_red = TRUE;
		return (add_new_redirect_in(infile, cmd));
	}
	else
		return (add_new_redirect_in(infile, NULL));
	return (NULL);
}

// this is where heredocs are ordered

t_ast	*order_heredoc(t_ast *cmd,char **tokens, int *i, int *head_red)
{
	char	*delimiter;

	*i = *i + 1;
	delimiter = ft_strdup(tokens[*i]);
	*i = *i + 1;
	if (*head_red == FALSE)
	{
		*head_red = TRUE;
		return (add_new_heredoc(delimiter, cmd));
	}
	else
		return (add_new_heredoc(delimiter, NULL));
	return (NULL);
}

// 0rder all kinds of redirections

t_ast	*order_redirection(t_ast *cmd,char **tokens, int *i, int *head_red)
{
	if (tokens[*i + 1] && tokens[*i][0] == '>')
		return (order_redirectout(cmd, tokens, i, head_red));
	else if (strcmp(tokens[*i], "<") == 0)
		return (order_redirectin(cmd, tokens, i, head_red));
	else if (strcmp(tokens[*i], "<<") == 0)
		return (order_heredoc(cmd, tokens, i, head_red));
	else
		*i = *i + 1;
	return (NULL);
}

// this function parses the command and redirecion chunks

t_ast	*parse_com_red(char **tokens, t_ast **astable, int *i, int *ascnt)
{
	int		com_researcher;
	t_ast	*cmd;
	int 	head_red;

	com_researcher = *i;
	head_red = FALSE;
	cmd = NULL;
	while ((tokens[com_researcher + 1] && (tokens[com_researcher][0] == '>' || tokens[com_researcher][0] == '<')) || (com_researcher > 0 && tokens[com_researcher + 1] && (tokens[com_researcher - 1][0] == '>' || tokens[com_researcher - 1][0] == '<')))
		com_researcher++;
	if (tokens[com_researcher] && tokens[com_researcher][0] != '|' && tokens[com_researcher][0] != '(' && tokens[com_researcher][0] != '&' && tokens[com_researcher][0] != ')')
	{
		astable[*ascnt] = order_command(tokens, &com_researcher);
		cmd = astable[*ascnt];
	}
	while (tokens[*i] && tokens[*i][0] != '|' && tokens[*i][0] != '(' && tokens[*i][0] != '&' && tokens[*i][0] != ')')
	{
		if (astable[*ascnt])
			*ascnt = *ascnt + 1;
		astable[*ascnt] = order_redirection(cmd, tokens, i,  &head_red);
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
	t_ast **astable = NULL;
	int i;
	int ascnt;

	i = 0;
	ascnt = 0;
	astable = ft_calloc(strtablen(tokens), sizeof(t_ast *));
	while (i < (int)strtablen(tokens))
	{
		cre_node(tokens, astable, &i, &ascnt);
		ascnt++;
	}
	astable[ascnt] = NULL;
	free_tokens(tokens , (int)strtablen(tokens));
	return (astable);
}
