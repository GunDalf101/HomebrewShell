/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing101.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlektaib <mlektaib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 21:35:05 by mbennani          #+#    #+#             */
/*   Updated: 2023/07/15 06:07:46 by mlektaib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing101.h"

int	and_counter(char *input)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (input[i + 1])
	{
		if (input[i] == '&' && input[i + 1] == '&')
			count++;
		i++;
	}
	return ((count + 1) * 2);
}

void	and_skips(t_paren *paren, char *input)
{
	while (input[paren->i] == '&')
	{
		paren->paren_input[paren->j] = input[paren->i];
		paren->j++;
		paren->i++;
	}
}

void	paren_maker(t_paren *paren, char *input, \
	t_quote_parenthesis *quotes, int *and_found)
{
	while (input[paren->i])
	{
		super_quote_hander(quotes, input[paren->i]);
		paren->foundand = FALSE;
		if (input[paren->i] == '&' && quotes->dubquo == FALSE
			&& quotes->sinquo == FALSE)
		{
			paren->foundand = TRUE;
			*and_found = TRUE;
			paren->paren_input[paren->j] = ')';
			paren->j++;
		}
		and_skips(paren, input);
		if (paren->foundand == TRUE && input[paren->i])
		{
			paren->paren_input[paren->j] = '(';
			paren->j++;
		}
		paren->paren_input[paren->j] = input[paren->i];
		paren->j++;
		paren->i++;
	}
}

char	*add_paren(char *input, t_quote_parenthesis *quotes)
{
	t_paren	paren;
	int		and_found;

	and_found = FALSE;
	paren.paren_input = ft_calloc(ft_strlen(input) + and_counter(input) + 1, 1);
	quotes->sinquo = FALSE;
	quotes->dubquo = FALSE;
	paren.i = 0;
	paren.j = 0;
	paren.paren_input[0] = '(';
	paren.j++;
	paren_maker(&paren, input, quotes, &and_found);
	paren.paren_input[paren.j] = ')';
	paren.paren_input[paren.j + 1] = '\0';
	if (and_found == FALSE)
	{
		paren.paren_input[0] = ' ';
		paren.paren_input[paren.j] = ' ';
	}
	return (paren.paren_input);
}

t_ast	*parsinginit(char *input, int subshell)
{
	t_ast				*root;
	char				*paren_input;
	t_ast				**lexical_table;
	char				**tokens;
	t_quote_parenthesis	quotes;

	root = NULL;
	if (!subshell)
	{
		paren_input = add_paren(input, &quotes);
		free(input);
	}
	else
		paren_input = input;
	tokens = tokenizer(paren_input, &quotes);
	if (!tokens)
		return (NULL);
	lexical_table = lex_luthor(tokens);
	if (!lexical_table)
		return (NULL);
	root = parse_tree(lexical_table);
	return (root);
}
