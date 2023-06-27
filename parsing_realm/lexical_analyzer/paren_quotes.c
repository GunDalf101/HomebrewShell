/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paren_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbennani <mbennani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 00:29:23 by mbennani          #+#    #+#             */
/*   Updated: 2023/06/22 02:24:47 by mbennani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexing_lexer.h"

// this is ft_split but with a twist
//(the whitespace between the quotes is skipped)

void	super_quote_hander(t_quote_parenthesis *quotes, char c)
{
	if (c == '\'' && quotes->dubquo == FALSE && quotes->sinquo == FALSE)
		quotes->sinquo = TRUE;
	else if (c == '\'' && quotes->sinquo == TRUE && quotes->dubquo == FALSE)
		quotes->sinquo = FALSE;
	if (c == '"' && quotes->dubquo == FALSE && quotes->sinquo == FALSE)
		quotes->dubquo = TRUE;
	else if (c == '"' && quotes->dubquo == TRUE && quotes->sinquo == FALSE)
		quotes->dubquo = FALSE;
}

int	isquote(char c)
{
	if (c == '"' || c == '\'')
		return (TRUE);
	return (FALSE);
}

void	parenthesis_life_time(char c, t_quote_parenthesis *quotes)
{
	if (c == '(' && quotes->sinquo == FALSE && quotes->dubquo == FALSE)
	{
		quotes->life_counter = quotes->life_counter + 1;
		quotes->paren = TRUE;
	}
	else if (c == ')' && quotes->sinquo == FALSE && quotes->dubquo == FALSE)
	{
		quotes->life_counter = quotes->life_counter - 1;
	}
	if (quotes->life_counter == 0 && quotes->paren == TRUE \
		&& quotes->sinquo == FALSE && quotes->dubquo == FALSE)
		quotes->paren = FALSE;
}
