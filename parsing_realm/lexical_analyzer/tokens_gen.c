/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_gen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbennani <mbennani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 21:50:45 by mbennani          #+#    #+#             */
/*   Updated: 2023/06/24 14:46:17 by mbennani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexing_lexer.h"

// this functions gets you free tokens or
// maybe does it FREE the tokens (guess we'll never know)

void	free_tokens(char **s, int j)
{
	int	i;

	i = 0;
	(void)j;
	while (s[i] && i < j)
	{
		free(s[i]);
		s[i] = NULL;
		i++;
	}
	free(s);
	s = NULL;
}

// function to to expand the input with a space next to the operators
// maybe i should skip later what's between spaces too???

char	*space_expand(char *input, t_quote_parenthesis *quotes)
{
	int		counter;
	char	*expansion;

	counter = 1;
	quotes->dubquo = FALSE;
	quotes->sinquo = FALSE;
	input_space_counter(input, quotes, &counter);
	// printf("counter: %d\n", counter);
	expansion = ft_calloc(counter + 1, 1);
	expansion[0] = ' ';
	input_spacer(input, quotes, expansion, counter);
	return (expansion);
}

char	**tokenizer(char *input, t_quote_parenthesis *quotes)
{
	char	*exp_input;
	char	**tokens;

	exp_input = NULL;
	tokens = NULL;
	quotes->sinquo = FALSE;
	quotes->dubquo = FALSE;
	exp_input = space_expand(input, quotes);
	free(input);
	if (input_syntax_checker(exp_input, quotes) == FAILURE)
		return (free(exp_input), NULL);
	tokens = split_with_a_twist(exp_input, ' ', quotes);
	free(exp_input);
	if (tokens == NULL)
		return (NULL);
	if (syntax_checker(tokens, quotes) == FAILURE)
		return (free_tokens(tokens, strtablen(tokens)), NULL);
	return (tokens);
}
