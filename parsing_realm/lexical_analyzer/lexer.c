/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbennani <mbennani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 21:50:47 by mbennani          #+#    #+#             */
/*   Updated: 2023/05/23 21:52:25 by mbennani         ###   ########.fr       */
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

t_ast	*order_command(char **tokens, t_ast **astable, int *i, int *ascnt)
{
	char	*cmd;
	char	**args;
	int		arg_count = 0;
	int		argcnt;
	int		tempi;


	(void)astable;
	arg_count = 0;
	argcnt = 0;
	cmd = ft_calloc(ft_strlen(tokens[*i]), 1);
	cmd = tokens[*i];
	*i = *i + 1;
	tempi = 1;
	while (tokens[tempi] && tokens[tempi][0] != '|' && tokens[tempi][0] != '(' && tokens[tempi][0] != '&')
	{
		if ((tokens[tempi] && (tokens[tempi][0] == '>' || tokens[tempi][0] == '<')) || (tokens[tempi] && tempi > 0 && (tokens[tempi - 1][0] == '>' || tokens[tempi - 1][0] == '<')))
			arg_count--;
		arg_count++;
		tempi++;
	}
	printf("---------<%d>------------\n", arg_count);
	args = calloc(arg_count + 1, sizeof(char *));
	while (tokens[*i] && tokens[*i][0] != '|' && tokens[*i][0] != '(' && tokens[*i][0] != '&')
	{
		while ((tokens[*i + 1] && (tokens[*i][0] == '>' || tokens[*i][0] == '<')) || (tokens[*i + 1] && *i > 0 && (tokens[*i - 1][0] == '>' || tokens[*i - 1][0] == '<')))
			*i = *i + 1;
		args[argcnt] = calloc(ft_strlen(tokens[*i]) + 1, 1);
		args[argcnt] = tokens[*i];
		*i = *i + 1;
		argcnt++;
	}
	return (add_new_cmd(cmd, args, arg_count, ast_cmd));
}

// this is where the output redirections are ordered

// t_ast	*order_redirectout(char **tokens, t_ast **astable, int *i, int *ascnt)
// {
	
// }

// this function parses the command and redirecion chunks

t_ast	*parse_com_red(char **tokens, t_ast **astable, int *i, int *ascnt)
{
	int		com_researcher;

	com_researcher = *i;
	while (tokens[com_researcher][0] == '>' || (com_researcher > 0 && tokens[com_researcher] && tokens[com_researcher - 1][0] == '>'))
		com_researcher++;
	astable[*ascnt] = order_command(tokens, astable, &com_researcher, ascnt);
	*i = *i + com_researcher;
	// if (tokens[*i][0] == '>')
	// 	return (order_redirectout(tokens, astable, i, ascnt));
	return (NULL);
}

// let's now create the nodes

t_ast	*cre_node(char **tokens, t_ast **astable, int *i, int *ascnt)
{
	if (*i == 0 || astable[*ascnt - 1]->type == ast_pipe || astable[*ascnt - 1]->type == ast_or || astable[*ascnt - 1]->type == ast_and || tokens[*i][0] == '<' || tokens[*i][0] == '>')
		parse_com_red(tokens, astable, i, ascnt);
	else if (strcmp(tokens[*i], "|") == 0)
		astable[*ascnt] = add_new_operation(ast_pipe, NULL, NULL);
	else if (strcmp(tokens[*i], "||") == 0)
		astable[*ascnt] = add_new_operation(ast_or, NULL, NULL);
	else if (strcmp(tokens[*i], "&&") == 0)
		astable[*ascnt] = add_new_operation(ast_and, NULL, NULL);
	return (NULL);
}

// this function is supposed to make up the nodes

t_ast	**lex_luthor(char **tokens)
{
	t_ast **astable = NULL;
	(void) tokens;
	int i;
	int j;
	int ascnt;

	i = 0;
	ascnt = 0;
	astable = ft_calloc(strtablen(tokens), sizeof(t_ast *));
	// return (NULL);
	while (tokens[i] != NULL)
	{
		astable[ascnt] = ft_calloc(1, sizeof(t_ast));
		cre_node(tokens, astable, &i, &ascnt);
		j = 0;
		while (j < astable[0]->u_data.cmd.arg_count)
		{
			printf("%s\n", astable[0]->u_data.cmd.args[j]);
			j++;
		}
		ascnt++;
	}
	return (astable);
}
