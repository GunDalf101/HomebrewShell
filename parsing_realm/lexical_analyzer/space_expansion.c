/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   space_expansion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbennani <mbennani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 01:47:40 by mbennani          #+#    #+#             */
/*   Updated: 2023/06/22 21:36:18 by mbennani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexing_lexer.h"

int	space_conditioner_before(char *input, int i, t_quote_parenthesis *quotes)
{
	if ((input[i + 1] == '(' || input[i + 1] == ')' || (input[i + 1] == '|' \
			&& input[i] != '|') || (input[i + 1] == '&' \
			&& input[i] != '&') || (input[i + 1] == '>' \
			&& input[i] != '>') || (input[i + 1] == '<' \
			&& input[i] != '<')) && (quotes->dubquo == FALSE \
			&& quotes->sinquo == FALSE))
		return (TRUE);
	return (FALSE);
}

int	space_conditioner_after(char *input, int i, t_quote_parenthesis *quotes)
{
	if ((input[i] == '(' || input[i] == ')' || (input[i + 1] != '|' \
				&& input[i] == '|') || (input[i + 1] != '&' \
				&& input[i] == '&') || (input[i + 1] != '>' \
				&& input[i] == '>') || (input[i + 1] != '<' \
				&& input[i] == '<')) && (quotes->dubquo == FALSE \
			&& quotes->sinquo == FALSE))
		return (TRUE);
	return (FALSE);
}

void	input_space_counter(char *input, t_quote_parenthesis *quotes, \
		int *counter)
{
	int	i;

	i = 0;
	while (input[i])
	{
		super_quote_hander(quotes, input[i]);
		if (space_conditioner_before(input, i, quotes) == TRUE)
			*counter = *counter + 1;
		if (space_conditioner_after(input, i, quotes) == TRUE)
			*counter = *counter + 1;
		*counter = *counter + 1;
		i++;
	}
}

void	input_spacer(char *input, t_quote_parenthesis *quotes, char *expansion, \
		int counter)
{
	int	i;
	int	j;

	i = 0;
	j = 1;
	while (input[i] && j < counter)
	{
		super_quote_hander(quotes, input[i]);
		expansion[j] = input[i];
		if (space_conditioner_before(input, i, quotes) == TRUE)
		{
			j++;
			expansion[j] = ' ';
		}
		if (space_conditioner_after(input, i, quotes) == TRUE)
		{
			expansion[j + 1] = ' ';
			j++;
		}
		if (input[i] == '\t')
			expansion[j] = ' ';
		j++;
		i++;
	}
	expansion[j] = '\0';
}
