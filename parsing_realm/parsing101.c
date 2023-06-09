/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing101.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbennani <mbennani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 21:35:05 by mbennani          #+#    #+#             */
/*   Updated: 2023/06/22 04:46:01 by mbennani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing101.h"

t_ast	*parsinginit(char *input)
{
	t_ast				*root;
	t_ast				**lexical_table;
	char				**tokens;
	t_quote_parenthesis	quotes;

	root = NULL;
	tokens = tokenizer(input, &quotes);
	if (!tokens)
		return (NULL);
	lexical_table = lex_luthor(tokens);
	if (!lexical_table)
		return (NULL);
	root = parse_tree(lexical_table);
	return (root);
}
