/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing101.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbennani <mbennani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 21:35:40 by mbennani          #+#    #+#             */
/*   Updated: 2023/07/13 02:49:24 by mbennani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING101_H
# define PARSING101_H

# include "ast/ast.h"
# include "lexical_analyzer/lexing_lexer.h"

t_ast	*parsinginit(char *input, int subshell);

#endif