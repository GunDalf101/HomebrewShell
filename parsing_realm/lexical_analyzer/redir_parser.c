/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbennani <mbennani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 01:59:46 by mbennani          #+#    #+#             */
/*   Updated: 2023/06/24 10:49:21 by mbennani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexing_lexer.h"

// this is where output redirections are ordered

t_ast	*order_redirectout(t_ast *cmd, char **tokens, int *i, int *head_red)
{
	char	*outfile;
	int		tag;

	tag = 0;
	if (ft_strcmp(tokens[*i], ">") == 0)
		tag = 1;
	else if (ft_strcmp(tokens[*i], ">>") == 0)
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

t_ast	*order_redirectin(t_ast *cmd, char **tokens, int *i, int *head_red)
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

t_ast	*order_heredoc(t_ast *cmd, char **tokens, int *i, int *head_red)
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

t_ast	*order_redirection(t_ast *cmd, char **tokens, int *i, int *head_red)
{
	if (tokens[*i + 1] && tokens[*i][0] == '>')
		return (order_redirectout(cmd, tokens, i, head_red));
	else if (ft_strcmp(tokens[*i], "<") == 0)
		return (order_redirectin(cmd, tokens, i, head_red));
	else if (ft_strcmp(tokens[*i], "<<") == 0)
		return (order_heredoc(cmd, tokens, i, head_red));
	else
		*i = *i + 1;
	return (NULL);
}
