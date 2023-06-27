/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing_lexer.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbennani <mbennani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 21:51:57 by mbennani          #+#    #+#             */
/*   Updated: 2023/06/24 23:18:58 by mbennani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXING_LEXER_H
# define LEXING_LEXER_H

# include "../../minishell.h"

typedef struct s_quote_parenthesis
{
	int	life_counter;
	int	paren;
	int	dubquo;
	int	sinquo;
}		t_quote_parenthesis;

int		syntax_checker(char **tokens, t_quote_parenthesis *quotes);
char	**tokenizer(char *input, t_quote_parenthesis *quotes);
t_ast	**lex_luthor(char **tokens);
char	**split_with_a_twist(char *s, char c, t_quote_parenthesis *quotes);
void	super_quote_hander(t_quote_parenthesis *quotes, char c);
int		isquote(char c);
void	parenthesis_life_time(char c, t_quote_parenthesis *quotes);
void	free_tokens(char **s, int j);
int		parenthesis_check_zo_extended(char c, int sinquo, int dubquo);
size_t	strtablen(char **tokens);
int		syntax_checker_extended(char **tokens, int i,
			t_quote_parenthesis *quotes);
int		pipe_check_extended(char **tokens, int i);
int		redirection_check_extended(char **tokens, int i);
int		rediretion_check(char **tokens, int i);
int		pipe_check(char **tokens, int i);
int		and_check(char **tokens, int i);
int		parenthesis_check_zo(char **tokens, int i, t_quote_parenthesis *quotes);
int		input_syntax_checker(char *input, t_quote_parenthesis *quotes);
int		space_conditioner_before(char *input, int i, \
			t_quote_parenthesis *quotes);
int		space_conditioner_after(char *input, int i, \
			t_quote_parenthesis *quotes);
void	input_space_counter(char *input, t_quote_parenthesis *quotes, \
			int *counter);
void	input_spacer(char *input, t_quote_parenthesis *quotes, char *expansion, \
			int counter);
t_ast	*order_redirection(t_ast *cmd, char **tokens, int *i, int *head_red);
t_ast	*order_command(char **tokens, int *i);
size_t	strtablen(char **tokens);
size_t	size_lol(char **tokens);

#endif