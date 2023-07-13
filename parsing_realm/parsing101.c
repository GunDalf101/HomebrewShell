/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing101.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlektaib <mlektaib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 21:35:05 by mbennani          #+#    #+#             */
/*   Updated: 2023/07/13 01:40:18 by mlektaib         ###   ########.fr       */
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

char	*add_paren(char *input, t_quote_parenthesis *quotes)
{
	char	*paren_input;
	int		i;
	int		j;
	int		foundand;

	paren_input = ft_calloc(ft_strlen(input) + and_counter(input) + 1, 1);
	quotes->sinquo = FALSE;
	quotes->dubquo = FALSE;
	i = 0;
	j = 0;
	paren_input[0] = '(';
	j++;
	while (input[i])
	{
		foundand = FALSE;
		if (input[i] == '&' && quotes->dubquo == FALSE && quotes->sinquo == FALSE)
		{
			paren_input[j] = ')';
			j++;
		}
		while (input[i] == '&')
		{
			paren_input[j] = input[i];
			j++;
			i++;
			foundand = TRUE;
		}
		if (foundand == TRUE)
		{
			paren_input[j] = '(';
			j++;
		}
		paren_input[j] = input[i];
		j++;
		i++;
	}
	paren_input[j] = ')';
	paren_input[j + 1] = '\0';
	return (paren_input);
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
