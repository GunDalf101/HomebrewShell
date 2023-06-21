/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_gen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbennani <mbennani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 21:50:45 by mbennani          #+#    #+#             */
/*   Updated: 2023/06/21 19:16:02 by mbennani         ###   ########.fr       */
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

char	*space_expand(char *input, int dubquo, int sinquo)
{
	int		i;
	int		j;
	int		counter;
	char	*expansion;

	i = 0;
	j = 1;
	counter = 1;
	dubquo = FALSE;
	sinquo = FALSE;
	while (input[i])
	{
		super_quote_hander(&dubquo, &sinquo, input[i]);
		if ((input[i + 1] == '(' || input[i + 1] == ')' || (input[i + 1] == '|' \
					&& input[i] != '|') || (input[i + 1] == '&' \
					&& input[i] != '&') || (input[i + 1] == '>' \
					&& input[i] != '>') || (input[i + 1] == '<' \
					&& input[i] != '<')) && (dubquo == FALSE \
				&& sinquo == FALSE))
			counter++;
		if ((input[i] == '(' || input[i] == ')' || (input[i + 1] != '|' \
					&& input[i] == '|') || (input[i + 1] != '&' \
					&& input[i] == '&') || (input[i + 1] != '>' \
					&& input[i] == '>') || (input[i + 1] != '<' \
					&& input[i] == '<')) && (dubquo == FALSE \
				&& sinquo == FALSE))
			counter++;
		counter++;
		i++;
	}
	i = 0;
	expansion = ft_calloc(counter + 1, 1);
	expansion[0] = ' ';
	while (input[i] && j < counter)
	{
		super_quote_hander(&dubquo, &sinquo, input[i]);
		expansion[j] = input[i];
		if ((input[i + 1] == '(' || input[i + 1] == ')' || (input[i + 1] == '|' \
					&& input[i] != '|') || (input[i + 1] == '&' \
					&& input[i] != '&') || (input[i + 1] == '>' \
					&& input[i] != '>') || (input[i + 1] == '<' \
					&& input[i] != '<')) && (dubquo == FALSE \
				&& sinquo == FALSE))
		{
			j++;
			expansion[j] = ' ';
		}
		if ((input[i] == '(' || input[i] == ')' || (input[i + 1] != '|' \
					&& input[i] == '|') || (input[i + 1] != '&' \
					&& input[i] == '&') || (input[i + 1] != '>' \
					&& input[i] == '>') || (input[i + 1] != '<' \
					&& input[i] == '<')) && (dubquo == FALSE \
				&& sinquo == FALSE))
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
	char	*exp_input;
	char	**tokens;
	int		dubquo;
	int		sinquo;

	exp_input = NULL;
	tokens = NULL;
	sinquo = FALSE;
	dubquo = FALSE;
	exp_input = space_expand(input, dubquo, sinquo);
	free(input);
	if (input_syntax_checker(exp_input) == FAILURE)
		return (free(exp_input), NULL);
	tokens = split_with_a_twist(exp_input, ' ');
	free(exp_input);
	if (tokens == NULL)
		return (NULL);
	if (syntax_checker(tokens) == FAILURE)
		return (free_tokens(tokens, strtablen(tokens)), NULL);
	return (tokens);
}
