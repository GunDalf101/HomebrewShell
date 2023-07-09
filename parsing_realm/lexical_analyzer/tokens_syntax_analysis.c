/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_syntax_analysis.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbennani <mbennani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 19:01:49 by mbennani          #+#    #+#             */
/*   Updated: 2023/07/08 18:34:03 by mbennani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexing_lexer.h"

extern t_global	g_global;
// are redirections cloned more than twice?

int	rediretion_check(char **tokens, int i)
{
	if (redirection_check_extended(tokens, i) == FAILURE)
		return (FAILURE);
	if (tokens[i + 1] == NULL || tokens[i + 1][0] == '\0')
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
	if (i == 0 && ft_strcmp(tokens[i], "|") == 0)
		return (printf("Error: syntax error near unexpected token `|'\n"), \
				FAILURE);
	else if (i == 0 && ft_strcmp(tokens[i], "||") == 0)
		return (printf("Error: syntax error near unexpected token `||'\n"), \
				FAILURE);
	else if (tokens[i + 1] == NULL || tokens[i + 1][0] == '\0')
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
	if (ft_strcmp(tokens[i], "&&") != 0)
		return (printf("Error: syntax error near unexpected token `&&'\n"), \
				FAILURE);
	if (i == 0)
		return (printf("Error: syntax error near unexpected token `&&'\n"), \
				FAILURE);
	else if (tokens[i + 1] == NULL || tokens[i + 1][0] == '\0')
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

int	parenthesis_check_zo(char **tokens, int i, t_quote_parenthesis *quotes)
{
	int	j;
	int	paren_status;

	j = 0;
	quotes->sinquo = FALSE;
	quotes->dubquo = FALSE;
	paren_status = FAILURE;
	if (i != 0 && (tokens[i - 1][0] != '|' || tokens[i - 1][0] != '&'))
		return (printf("Error: syntax error near unexpected token `('\n"), \
				FAILURE);
	while (tokens[i][j])
	{
		super_quote_hander(quotes, tokens[i][j]);
		if (closing_parentesis(tokens[i]) == FAILURE)
			return (FAILURE);
		paren_status = parenthesis_check_zo_extended (tokens[i][j], \
		quotes->sinquo, quotes->dubquo);
		if (paren_status == FAILURE)
			return (FAILURE);
		else if (paren_status == SUCCESS)
			return (SUCCESS);
		j++;
	}
	return (SUCCESS);
}

//  this function checks every possible syntax error

int	syntax_checker(char **tokens, t_quote_parenthesis *quotes)
{
	int	i;

	i = 0;
	while (tokens[i])
	{
		if (syntax_checker_extended(tokens, i, quotes) == FAILURE)
			return (g_global.exit_status = (unsigned char)258, FAILURE);
		i++;
	}
	return (SUCCESS);
}
