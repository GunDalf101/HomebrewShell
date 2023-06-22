/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_syntax_analysis_extended.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbennani <mbennani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 19:01:49 by mbennani          #+#    #+#             */
/*   Updated: 2023/06/22 05:30:11 by mbennani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexing_lexer.h"

// are redirections cloned more than twice?

int	redirection_check_extended(char **tokens, int i)
{
	if (!tokens[i])
		return (SUCCESS);
	if (strcmp(tokens[i], ">>") != 0 && strcmp(tokens[i], ">") != 0
		&& strcmp(tokens[i], "<<") != 0 && strcmp(tokens[i], "<") != 0)
	{
		if (strcmp(tokens[i], ">>>") == 0)
			return (printf("Error: syntax error near unexpected token `>'\n"), \
					FAILURE);
		else if (strcmp(tokens[i], "<<<") == 0)
			return (printf("Error: syntax error near unexpected token `<'\n"), \
					FAILURE);
		else if (tokens[i][0] == '>')
			return (printf("Error: syntax error near unexpected token `>>'\n"), \
					FAILURE);
		else
			return (printf("Error: syntax error near unexpected token `<<'\n"), \
					FAILURE);
	}
	return (SUCCESS);
}

int	pipe_check_extended(char **tokens, int i)
{
	if (!tokens[i])
		return (SUCCESS);
	if (strcmp(tokens[i], "||") != 0 && strcmp(tokens[i], "|") != 0)
	{
		if (strcmp(tokens[i], "|||") == 0)
			return (printf("Error: syntax error near unexpected token `|'\n"), \
					FAILURE);
		else
			return (printf("Error: syntax error near unexpected token `||'\n"), \
					FAILURE);
	}
	return (SUCCESS);
}

int	parenthesis_check_zo_extended(char c, int sinquo, int dubquo)
{
	if (c == '(')
		return (-1);
	else if (c == 41 && sinquo == FALSE && dubquo == FALSE)
		return (printf("Error: syntax error near unexpected token `)'\n"), \
				FAILURE);
	else if (c == '|' && sinquo == FALSE && dubquo == FALSE)
		return (printf("Error: syntax error near unexpected token `|'\n"), \
				FAILURE);
	else if (c == '&' && sinquo == FALSE && dubquo == FALSE)
		return (printf("Error: syntax error near unexpected token `&'\n"), \
				FAILURE);
	else if (c != ' ' && sinquo == FALSE && dubquo == FALSE)
		return (SUCCESS);
	return (-1);
}

int	syntax_checker_extended(char **tokens, int i, t_quote_parenthesis *quotes)
{
	if (!tokens[i])
		return (SUCCESS);
	if ((tokens[i][0] == '>' || tokens[i][0] == '<'))
	{
		if (rediretion_check(tokens, i) == FAILURE)
			return (FAILURE);
	}
	else if (tokens[i][0] == '|')
	{
		if (pipe_check(tokens, i) == FAILURE)
			return (FAILURE);
	}
	else if (tokens[i][0] == '&')
	{
		if (and_check(tokens, i) == FAILURE)
			return (FAILURE);
	}
	else if (tokens[i][0] == '(')
	{
		if (parenthesis_check_zo(tokens, i, quotes) == FAILURE)
			return (FAILURE);
	}
	return (SUCCESS);
}
