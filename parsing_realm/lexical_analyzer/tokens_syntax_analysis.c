/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_syntax_analysis.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbennani <mbennani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 19:01:49 by mbennani          #+#    #+#             */
/*   Updated: 2023/06/19 21:13:37 by mbennani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexing_lexer.h"

// are redirections cloned more than twice?

int	rediretion_check(char **tokens, int i)
{
	if (redirection_check_extended(tokens, i) == FAILURE)
		return (FAILURE);
	if (tokens[i + 1] == NULL)
		return (printf("Error: syntax error near unexpected token `newline'\n"), \
				FAILURE);
	else if (tokens[i + 1][0] == '>')
		return (printf("Error: syntax error near unexpected token `>'\n"), \
				FAILURE);
	else if (tokens[i + 1][0] == '<')
		return (printf("Error: syntax error near unexpected token `<'\n"), \
				FAILURE);
	else if (tokens[i + 1][0] == '|')
		return (printf("Error: syntax error near unexpected token `|'\n"), \
				FAILURE);
	else if (tokens[i + 1][0] == '&')
		return (printf("Error: syntax error near unexpected token `&'\n"), \
				FAILURE);
	return (SUCCESS);
}

int	pipe_check(char **tokens, int i)
{
	if (pipe_check_extended(tokens, i) == FAILURE)
		return (FAILURE);
	if (i == 0 && strcmp(tokens[i], "|") == 0)
		return (printf("Error: syntax error near unexpected token `|'\n"), \
				FAILURE);
	else if (i == 0 && strcmp(tokens[i], "||") == 0)
		return (printf("Error: syntax error near unexpected token `||'\n"), \
				FAILURE);
	else if (tokens[i + 1] == NULL)
		return (printf("Error: syntax error near unexpected token `newline'\n"), \
				FAILURE);
	else if (tokens[i + 1][0] == '|')
		return (printf("Error: syntax error near unexpected token `|'\n"), \
				FAILURE);
	else if (tokens[i + 1][0] == '>')
		return (rediretion_check(tokens, i + 1));
	else if (tokens[i + 1][0] == '<')
		return (rediretion_check(tokens, i + 1));
	else if (tokens[i + 1][0] == '&')
		return (printf("Error: syntax error near unexpected token `&'\n"), \
				FAILURE);
	return (SUCCESS);
}

int	and_check(char **tokens, int i)
{
	if (strcmp(tokens[i], "&&") != 0)
		return (printf("Error: syntax error near unexpected token `&&'\n"), \
				FAILURE);
	if (i == 0)
		return (printf("Error: syntax error near unexpected token `&&'\n"), \
				FAILURE);
	else if (tokens[i + 1] == NULL)
		return (printf("Error: syntax error near unexpected token `newline'\n"), \
				FAILURE);
	else if (tokens[i + 1][0] == '&')
		return (printf("Error: syntax error near unexpected token `&'\n"), \
				FAILURE);
	else if (tokens[i + 1][0] == '>')
		return (rediretion_check(tokens, i + 1));
	else if (tokens[i + 1][0] == '<')
		return (rediretion_check(tokens, i + 1));
	else if (tokens[i + 1][0] == '|')
		return (printf("Error: syntax error near unexpected token `|'\n"), \
				FAILURE);
	return (SUCCESS);
}

int	parenthesis_check_zo(char **tokens, int i)
{
	int	j;

	j = 1;
	while (tokens[i][j] && j++)
	{
		if (tokens[i][j] == 0)
			return (printf("Error: syntax error near unexpected token `\\n'\n"), \
				FAILURE);
		else if (tokens[i][j] == ')')
			return (printf("Error: syntax error near unexpected token `)'\n"), \
					FAILURE);
		else if (tokens[i][j] == '>')
			return (rediretion_check(tokens, i + 1));
		else if (tokens[i][j] == '<')
			return (rediretion_check(tokens, i + 1));
		else if (tokens[i][j] == '|')
			return (printf("Error: syntax error near unexpected token `|'\n"), \
					FAILURE);
		else if (tokens[i][j] == '&')
			return (printf("Error: syntax error near unexpected token `&'\n"), \
					FAILURE);
		else if (tokens[i][j] != ' ')
			return (SUCCESS);
	}
	return (SUCCESS);
}

//  this function checks every possible syntax error

int	syntax_checker(char **tokens)
{
	int	i;
	int	dubquo;
	int	sinquo;

	i = 0;
	dubquo = FALSE;
	sinquo = FALSE;
	while (tokens[i])
	{
		super_quote_hander(&dubquo, &sinquo, tokens[i][0]);
		if (syntax_checker_extended(tokens, i, dubquo, sinquo) == FAILURE)
			return (FAILURE);
		i++;
	}
	return (SUCCESS);
}
