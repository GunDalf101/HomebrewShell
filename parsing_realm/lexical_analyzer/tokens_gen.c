/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_gen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbennani <mbennani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 21:50:45 by mbennani          #+#    #+#             */
/*   Updated: 2023/05/24 11:41:22 by mbennani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexing_lexer.h"

// this functions gets you free tokens or maybe does it FREE the tokens (guess we'll never know)

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

//  this function checks every possible syntax error

int	syntax_checker(char **tokens)
{
	(void)tokens;

	return (0);
}

// function to to expand the input with a space next to the operators
// maybe i should skip later what's between spaces too???

char	*space_expand(char *input)
{
	int		i = 0;
	int		j = 0;
	int		it = 0;
	int		counter = 0;
	char	*expansion;
	int	dubquo;
	int	sinquo;

	dubquo = FALSE;
	sinquo = FALSE;
	while(input[it])
	{
		super_quote_hander(&dubquo, &sinquo, input[it]);
		if ((input[it + 1] == '(' || input[it + 1] == ')' || (input[it + 1] == '|' && input[it] != '|') || (input[it + 1] == '&' && input[it] != '&') || (input[it + 1] == '>' && input[it] != '>') || (input[it + 1] == '<' && input[it] != '<')) && (dubquo == FALSE && sinquo == FALSE))
			counter++;
		if ((input[it] == '(' || input[it] == ')' || (input[it + 1] != '|' && input[it] == '|') || (input[it + 1] != '&' && input[it] == '&') || (input[it + 1] != '>' && input[it] == '>') || (input[it + 1] != '<' && input[it] == '<')) && (dubquo == FALSE && sinquo == FALSE))
			counter++;
		it++;
	}
	counter+=it;
	expansion = ft_calloc(counter + 1, 1);
	while(input[i])
	{
		super_quote_hander(&dubquo, &sinquo, input[i]);
		expansion[j] = input[i];
		if ((input[i + 1] == '(' || input[i + 1] == ')' || (input[i + 1] == '|' && input[i] != '|') || (input[i + 1] == '&' && input[i] != '&') || (input[i + 1] == '>' && input[i] != '>') || (input[i + 1] == '<' && input[i] != '<')) && (dubquo == FALSE && sinquo == FALSE))
		{
			j++;
			expansion[j] = ' ';
		}
		if ((input[i] == '(' || input[i] == ')' || (input[i + 1] != '|' && input[i] == '|') || (input[i + 1] != '&' && input[i] == '&') || (input[i + 1] != '>' && input[i] == '>') || (input[i + 1] != '<' && input[i] == '<')) && (dubquo == FALSE && sinquo == FALSE))
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
	tokens = split_with_a_twist(exp_input, ' ');
	if (syntax_checker(tokens) == FAILURE)
		return(free_tokens(tokens), error_thrower(0), NULL);
	return (tokens);
}