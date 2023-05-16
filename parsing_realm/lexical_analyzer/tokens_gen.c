/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_gen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbennani <mbennani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 21:50:45 by mbennani          #+#    #+#             */
/*   Updated: 2023/05/16 23:32:27 by mbennani         ###   ########.fr       */
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

char	*space_expand(char *input)
{
	int		i = 0;
	int		j = 0;
	int		it = 0;
	char	*expansion;

	while(input[it])
	{
		if (input[it + 1] == '(' || input[it + 1] == ')' || (input[it + 1] == '|' && input[it] != '|') || (input[it + 1] == '&' && input[it] != '&') || (input[it + 1] == '>' && input[it] != '>') || (input[it + 1] == '<' && input[it] != '<'))
			it++;
		if (input[it] == '(' || input[it] == ')' || (input[it + 1] != '|' && input[it] == '|') || (input[it + 1] != '&' && input[it] == '&') || (input[it + 1] != '>' && input[it] == '>') || (input[it + 1] != '<' && input[it] == '<'))
			it++;
		it++;
	}
	expansion = ft_calloc(it + 1, 1);
	while(input[i])
	{
		expansion[j] = input[i];
		if ((input[i + 1] == '(' || input[i + 1] == ')' || (input[i + 1] == '|' && input[i] != '|') || (input[i + 1] == '&' && input[i] != '&') || (input[i + 1] == '>' && input[i] != '>') || (input[i + 1] == '<' && input[i] != '<')))
		{
			j++;
			expansion[j] = ' ';
		}
		if ((input[i] == '(' || input[i] == ')' || (input[i + 1] != '|' && input[i] == '|') || (input[i + 1] != '&' && input[i] == '&') || (input[i + 1] != '>' && input[i] == '>') || (input[i + 1] != '<' && input[i] == '<')))
		{
			expansion[j + 1] = ' ';
			j++;
		}
		j++;
		i++;
	}
	expansion[j] = '\0';
	return (expansion);
}

char	**tokenizer(char *input)
{
	char	*exp_input = NULL;
	char	**tokens = NULL;

	exp_input = space_expand(input);
	tokens = ft_split(exp_input, ' ');
	if (syntax_checker(tokens) == FAILURE)
		return(free_tokens(tokens), error_thrower(0), NULL);
	return (tokens);
}