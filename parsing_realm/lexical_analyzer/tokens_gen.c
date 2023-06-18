/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_gen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbennani <mbennani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 21:50:45 by mbennani          #+#    #+#             */
/*   Updated: 2023/06/18 09:54:22 by mbennani         ###   ########.fr       */
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

// are redirections cloned more than twice?

int	rediretion_check(char **tokens, int i)
{
	if (strcmp(tokens[i], ">>") != 0 && strcmp(tokens[i], ">") != 0 && strcmp(tokens[i], "<<") != 0 && strcmp(tokens[i], "<") != 0)
	{
		if (strcmp(tokens[i], ">>>") == 0)
			return (printf("Error: syntax error near unexpected token `>'\n"), FAILURE);
		else if (strcmp(tokens[i], "<<<") == 0)
			return (printf("Error: syntax error near unexpected token `<'\n"), FAILURE);
		else if (tokens[i][0] == '>')
			return (printf("Error: syntax error near unexpected token `>>'\n"), FAILURE);
		else
			return (printf("Error: syntax error near unexpected token `<<'\n"), FAILURE);
	}
	if (tokens[i + 1] == NULL)
		return (printf("Error: syntax error near unexpected token `newline'\n"), FAILURE);
	else if (tokens[i + 1][0] == '>')
		return (printf("Error: syntax error near unexpected token `>'\n"), FAILURE);
	else if (tokens[i + 1][0] == '<')
		return (printf("Error: syntax error near unexpected token `<'\n"), FAILURE);
	else if (tokens[i + 1][0] == '|')
		return (printf("Error: syntax error near unexpected token `|'\n"), FAILURE);
	else if (tokens[i + 1][0] == '&')
		return (printf("Error: syntax error near unexpected token `&'\n"), FAILURE);
	return (SUCCESS);
}

int	pipe_check(char **tokens, int i)
{
	if (strcmp(tokens[i], "||") != 0 && strcmp(tokens[i], "|") != 0)
	{
		if (strcmp(tokens[i], "|||") == 0)
			return (printf("Error: syntax error near unexpected token `|'\n"), FAILURE);
		else
			return (printf("Error: syntax error near unexpected token `||'\n"), FAILURE);
	}
	if (i == 0 && strcmp(tokens[i], "|") == 0)
		return (printf("Error: syntax error near unexpected token `|'\n"), FAILURE);
	else if (i == 0 && strcmp(tokens[i], "||") == 0)
		return (printf("Error: syntax error near unexpected token `||'\n"), FAILURE);
	else if (tokens[i + 1] == NULL)
		return (printf("Error: syntax error near unexpected token `newline'\n"), FAILURE);
	else if (tokens[i + 1][0] == '|')
		return (printf("Error: syntax error near unexpected token `|'\n"), FAILURE);
	else if (tokens[i + 1][0] == '>')
		return (rediretion_check(tokens, i + 1));
	else if (tokens[i + 1][0] == '<')
		return (rediretion_check(tokens, i + 1));
	else if (tokens[i + 1][0] == '&')
		return (printf("Error: syntax error near unexpected token `&'\n"), FAILURE);
	return (SUCCESS);
}

int	and_check(char **tokens, int i)
{
	if (strcmp(tokens[i], "&&") != 0)
		return (printf("Error: syntax error near unexpected token `&&'\n"), FAILURE);
	if (i == 0)
		return (printf("Error: syntax error near unexpected token `&&'\n"), FAILURE);
	else if (tokens[i + 1] == NULL)
		return (printf("Error: syntax error near unexpected token `newline'\n"), FAILURE);
	else if (tokens[i + 1][0] == '&')
		return (printf("Error: syntax error near unexpected token `&'\n"), FAILURE);
	else if (tokens[i + 1][0] == '>')
		return (rediretion_check(tokens, i + 1));
	else if (tokens[i + 1][0] == '<')
		return (rediretion_check(tokens, i + 1));
	else if (tokens[i + 1][0] == '|')
		return (printf("Error: syntax error near unexpected token `|'\n"), FAILURE);
	return (SUCCESS);
}

//  this function checks every possible syntax error

int	syntax_checker(char **tokens)
{
	int	i = 0;
	int	dubquo = FALSE;
	int	sinquo = FALSE;

	while (tokens[i])
	{
		super_quote_hander(&dubquo, &sinquo, tokens[i][0]);
		if ((tokens[i][0] == '>' || tokens[i][0] == '<') && dubquo == FALSE && sinquo == FALSE)
		{
			if (rediretion_check(tokens, i) == FAILURE)
				return (FAILURE);
		}
		else if (tokens[i][0] == '|' && dubquo == FALSE && sinquo == FALSE)
		{
			if (pipe_check(tokens, i) == FAILURE)
				return (FAILURE);
		}
		else if (tokens[i][0] == '&' && dubquo == FALSE && sinquo == FALSE)
		{
			if (and_check(tokens, i) == FAILURE)
				return (FAILURE);
		}
		i++;
	}
	return (0);
}

// are parenthesis balanced(odd or even)?

int	parenthesis_check(char *input)
{
	int	i = 0;
	int	life_counter = 0;
	int	paren = FALSE;
	int	dubquo = FALSE;
	int	sinquo = FALSE;

	while(input[i])
	{
		super_quote_hander(&dubquo, &sinquo, input[i]);
		parenthesis_life_time(&life_counter, input[i], &paren, sinquo, dubquo);
		i++;
	}
	if (life_counter < 0)
	{
		printf("Error: syntax error near unexpected token `)'\n");
		return (FAILURE);
	}
	if (life_counter != 0 || paren == TRUE)
	{
		printf("Error: parenthesis unclosed\n");
		return (FAILURE);
	}
	return (SUCCESS);
}

// are the quotes closed thight?

int	quotes_check(char *input)
{
	int	i = 0;
	int	dubquo = FALSE;
	int	sinquo = FALSE;

	while(input[i])
	{
		super_quote_hander(&dubquo, &sinquo, input[i]);
		i++;
	}
	if (dubquo == TRUE)
	{
		printf("Error: double quote unclosed\n");
		return (FAILURE);
	}
	if (sinquo == TRUE)
	{
		printf("Error: single quote unclosed\n");
		return (FAILURE);
	}
	return (SUCCESS);
}

// no semicolons allowed

int	semicolon_check(char *input)
{
	int	i = 0;
	int	dubquo = FALSE;
	int	sinquo = FALSE;

	while(input[i])
	{
		super_quote_hander(&dubquo, &sinquo, input[i]);
		if (input[i] == ';' && dubquo == FALSE && sinquo == FALSE)
		{
			printf("Error: syntax error near unexpected token `;'\n");
			return (FAILURE);
		}
		i++;
	}
	return (SUCCESS);
}

//  this function checks every possible syntax error

int input_syntax_checker(char *input)
{
	if (parenthesis_check(input) == FAILURE)
		return (FAILURE);
	if (quotes_check(input) == FAILURE)
		return (FAILURE);
	if (semicolon_check(input) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

// function to to expand the input with a space next to the operators
// maybe i should skip later what's between spaces too???

char	*space_expand(char *input)
{
	int		i = 0;
	int		j = 1;
	int		it = 0;
	int		counter = 1;
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
	expansion[0] = ' ';
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
	if (input_syntax_checker(exp_input) == FAILURE)
		return (NULL);
	tokens = split_with_a_twist(exp_input, ' ');
	if (tokens == NULL)
		return (NULL);
	if (syntax_checker(tokens) == FAILURE)
		return(free_tokens(tokens), NULL);
	return (tokens);
}