/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_gen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbennani <mbennani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 21:50:45 by mbennani          #+#    #+#             */
/*   Updated: 2023/05/16 15:36:09 by mbennani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "lexing_lexer.h"

void free_tokens(char **s)
{
	int	i;

	i = 0;
	while (i >= 0 && s[i] != NULL)
	{
		free(s[i]);
		s[i] = NULL;
		i--;
	}
	free(s);
	s = NULL;
}

int	syntax_checker(char **tokens)
{
	(void)tokens;

	return (0);
}

char	**space_expand(char **inittokens)
{
	(void)inittokens;
	char	**tokens = NULL;

	return (tokens);
}

char	**tokenizer(char *input)
{
	char	**tokens = NULL;
	char	**exp_tokens = NULL;

	tokens = ft_split(input, ' ');
	exp_tokens = space_expand(tokens);
	if (syntax_checker(tokens) == FAILURE)
		return(free_tokens(tokens), error_thrower(0), NULL);
	return (tokens);
}