/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing101.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlektaib <mlektaib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 21:35:05 by mbennani          #+#    #+#             */
/*   Updated: 2023/06/08 15:25:44 by mlektaib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "parsing101.h"

t_ast	*parsinginit(char	*input)
{
	t_ast	*root;
	t_ast	**lexical_table;
	char	**tokens;

	tokens = tokenizer(input);
	lexical_table = lex_luthor(tokens);
	root = parse_tree(lexical_table);

	return (root);
}