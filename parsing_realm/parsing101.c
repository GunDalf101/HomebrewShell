/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing101.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbennani <mbennani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 21:35:05 by mbennani          #+#    #+#             */
/*   Updated: 2023/06/18 02:14:10 by mbennani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "parsing101.h"

t_ast	*parsinginit(char	*input)
{
	t_ast	*root;
	t_ast	**lexical_table;
	char	**tokens;

	tokens = tokenizer(input);
	if (!tokens)
		return (NULL);
	lexical_table = lex_luthor(tokens);
	if (!lexical_table)
		return (NULL);
	root = parse_tree(lexical_table);
	return (root);
}