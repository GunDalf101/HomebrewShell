/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_syntax_analysis.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbennani <mbennani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 19:01:44 by mbennani          #+#    #+#             */
/*   Updated: 2023/06/19 21:18:36 by mbennani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexing_lexer.h"

// are parenthesis balanced(odd or even)?

int	parenthesis_check(char *input)
{
	int	i;
	int	life_counter;
	int	paren;
	int	dubquo;
	int	sinquo;

	i = 0;
	life_counter = 0;
	paren = FALSE;
	dubquo = FALSE;
	sinquo = FALSE;
	while (input[i])
	{
		super_quote_hander(&dubquo, &sinquo, input[i]);
		parenthesis_life_time(&life_counter, input[i], &paren, sinquo, dubquo);
		if (life_counter < 0)
			return (printf("Error: syntax error near unexpected token `)'\n"), \
					FAILURE);
		i++;
	}
	if (life_counter != 0 || paren == TRUE)
		return (printf("Error: parenthesis unclosed\n"), FAILURE);
	return (SUCCESS);
}

// are the quotes closed thight?

int	quotes_check(char *input)
{
	int	i;
	int	dubquo;
	int	sinquo;

	i = 0;
	dubquo = FALSE;
	sinquo = FALSE;
	while (input[i])
	{
		super_quote_hander(&dubquo, &sinquo, input[i]);
		i++;
	}
	if (dubquo == TRUE)
	{
		printf("Error: double quote unclosed\n");
		return (FAILURE);
	}
	if (sinquo == TRUE)
	{
		printf("Error: single quote unclosed\n");
		return (FAILURE);
	}
	return (SUCCESS);
}

// no semicolons allowed

int	semicolon_check(char *input)
{
	int	i;
	int	dubquo;
	int	sinquo;

	i = 0;
	dubquo = FALSE;
	sinquo = FALSE;
	while (input[i])
	{
		super_quote_hander(&dubquo, &sinquo, input[i]);
		if (input[i] == ';' && dubquo == FALSE && sinquo == FALSE)
		{
			printf("Error: syntax error near unexpected token `;'\n");
			return (FAILURE);
		}
		i++;
	}
	return (SUCCESS);
}

//  this function checks every possible syntax error

int	input_syntax_checker(char *input)
{
	if (parenthesis_check(input) == FAILURE)
		return (FAILURE);
	if (quotes_check(input) == FAILURE)
		return (FAILURE);
	if (semicolon_check(input) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}
