/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing_lexer.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbennani <mbennani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 21:51:57 by mbennani          #+#    #+#             */
/*   Updated: 2023/05/23 14:17:55 by mbennani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXING_LEXER_H
# define LEXING_LEXER_H

# include "../../minishell.h"

char	**tokenizer(char *input);
t_ast	**lex_luthor(char **tokens);
char	**split_with_a_twist(char const *s, char c);
void	super_quote_hander(int *dubquo, int *sinquo, char c);

#endif