/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_syntax_analysis_extended.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbennani <mbennani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 19:01:49 by mbennani          #+#    #+#             */
/*   Updated: 2023/07/08 18:35:53 by mbennani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexing_lexer.h"

// are redirections cloned more than twice?

int	closing_parentesis(char *token)
{
	int	j;
	int	closed;

	j = 0;
	closed = FALSE;
	while (token[j])
	{
		if (token[j] == ')')
		{
			closed = TRUE;
			j++;
			continue ;
		}
		if (closed == TRUE && token[j] != ' ' && token[j] != '\0')
		{
			if (token[j] == '>' || token[j] == '<' || token[j] == '|' || \
			token[j] == '&')
				closed = FALSE;
			else
				return (printf("Error: syntax error near unexpected token \
`)'\n"), FAILURE);
		}
		j++;
	}
	return (SUCCESS);
}

int	redirection_check_extended(char **tokens, int i)
{
	if (!tokens[i])
		return (SUCCESS);
	if (ft_strcmp(tokens[i], ">>") != 0 && ft_strcmp(tokens[i], ">") != 0
		&& ft_strcmp(tokens[i], "<<") != 0 && ft_strcmp(tokens[i], "<") != 0)
	{
		if (ft_strcmp(tokens[i], ">>>") == 0)
			return (printf("Error: syntax error near unexpected token `>'\n"), \
					FAILURE);
		else if (ft_strcmp(tokens[i], "<<<") == 0)
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
	if (ft_strcmp(tokens[i], "||") != 0 && ft_strcmp(tokens[i], "|") != 0)
	{
		if (ft_strcmp(tokens[i], "|||") == 0)
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
	else if (c != '\0' && sinquo == FALSE && dubquo == FALSE)
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
