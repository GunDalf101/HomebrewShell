/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing_lexer.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbennani <mbennani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 21:51:57 by mbennani          #+#    #+#             */
/*   Updated: 2023/06/20 07:47:38 by mbennani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXING_LEXER_H
# define LEXING_LEXER_H

# include "../../minishell.h"

int		syntax_checker(char **tokens);
char	**tokenizer(char *input);
t_ast	**lex_luthor(char **tokens);
char	**split_with_a_twist(char  *s, char c);
void	super_quote_hander(int *dubquo, int *sinquo, char c);
void	parenthesis_life_time(int *life_counter, char c, int *paren, int sinquo,
			int dubquo);
void	free_tokens(char **s, int j);
size_t	strtablen(char **tokens);
int		syntax_checker_extended(char **tokens, int i);
int		pipe_check_extended(char **tokens, int i);
int		redirection_check_extended(char **tokens, int i);
int		rediretion_check(char **tokens, int i);
int		pipe_check(char **tokens, int i);
int		and_check(char **tokens, int i);
int		parenthesis_check_zo(char **tokens, int i);
int		input_syntax_checker(char *input);

#endif