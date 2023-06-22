/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_syntax_analysis.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbennani <mbennani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 19:01:44 by mbennani          #+#    #+#             */
/*   Updated: 2023/06/22 02:25:49 by mbennani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexing_lexer.h"

// are parenthesis balanced(odd or even)?

int	parenthesis_check(char *input, t_quote_parenthesis *quotes)
{
	int	i;

	i = 0;
	quotes->life_counter = 0;
	quotes->paren = FALSE;
	quotes->dubquo = FALSE;
	quotes->sinquo = FALSE;
	while (input[i])
	{
		super_quote_hander(quotes, input[i]);
		parenthesis_life_time(input[i], quotes);
		if (quotes->life_counter < 0)
			return (printf("Error: syntax error near unexpected token `)'\n"), \
					FAILURE);
		i++;
	}
	if (quotes->life_counter != 0 || quotes->paren == TRUE)
		return (printf("Error: parenthesis unclosed\n"), FAILURE);
	return (SUCCESS);
}

// are the quotes closed thight?

int	quotes_check(char *input, t_quote_parenthesis *quotes)
{
	int	i;

	i = 0;
	quotes->dubquo = FALSE;
	quotes->sinquo = FALSE;
	while (input[i])
	{
		super_quote_hander(quotes, input[i]);
		i++;
	}
	if (quotes->dubquo == TRUE)
	{
		printf("Error: double quote unclosed\n");
		return (FAILURE);
	}
	if (quotes->sinquo == TRUE)
	{
		printf("Error: single quote unclosed\n");
		return (FAILURE);
	}
	return (SUCCESS);
}

// no semicolons allowed

int	semicolon_check(char *input, t_quote_parenthesis *quotes)
{
	int	i;

	i = 0;
	quotes->dubquo = FALSE;
	quotes->sinquo = FALSE;
	while (input[i])
	{
		super_quote_hander(quotes, input[i]);
		if (input[i] == ';' && quotes->dubquo == FALSE \
			&& quotes->sinquo == FALSE)
		{
			printf("Error: syntax error near unexpected token `;'\n");
			return (FAILURE);
		}
		i++;
	}
	return (SUCCESS);
}

//  this function checks every possible syntax error

int	input_syntax_checker(char *input, t_quote_parenthesis *quotes)
{
	if (parenthesis_check(input, quotes) == FAILURE)
		return (FAILURE);
	if (quotes_check(input, quotes) == FAILURE)
		return (FAILURE);
	if (semicolon_check(input, quotes) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}
