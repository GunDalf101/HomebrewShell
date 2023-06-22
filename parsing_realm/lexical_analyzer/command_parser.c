/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbennani <mbennani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 02:04:59 by mbennani          #+#    #+#             */
/*   Updated: 2023/06/22 02:28:09 by mbennani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexing_lexer.h"

void	what_about_args(char **tokens, int *i, char **args)
{
	int		argcnt;

	argcnt = 0;
	while (tokens[*i] && tokens[*i][0] != '|' && tokens[*i][0] != '(' \
		&& tokens[*i][0] != '&' && tokens[*i][0] != ')')
	{
		while ((tokens[*i] && (tokens[*i][0] == '>' || tokens[*i][0] == '<'))
			|| (tokens[*i] && *i > 0 && (tokens[*i - 1][0] == '>' || tokens[*i
					- 1][0] == '<')))
			*i = *i + 1;
		if (!tokens[*i] || tokens[*i][0] == '|' || tokens[*i][0] == '(' \
			|| tokens[*i][0] == '&' || tokens[*i][0] == ')')
			break ;
		args[argcnt] = ft_strdup(tokens[*i]);
		*i = *i + 1;
		argcnt++;
	}
}

int	what_condition(char **tokens, int *tempi)
{
	if ((tokens[*tempi] && (tokens[*tempi][0] == '>' || \
		tokens[*tempi][0] == '<'))
		|| (tokens[*tempi] && *tempi > 0 && (tokens[*tempi - 1][0] == '>'
				|| tokens[*tempi - 1][0] == '<')))
		return (TRUE);
	return (FALSE);
}

// this is where the output commands are ordered

t_ast	*order_command(char **tokens, int *i)
{
	char	*cmd;
	char	**args;
	int		arg_count;
	int		tempi;

	arg_count = 0;
	tempi = *i;
	if (what_condition(tokens, &tempi) == TRUE)
		return (NULL);
	cmd = ft_strdup(tokens[*i]);
	while (tokens[tempi] && tokens[tempi][0] != '|' && tokens[tempi][0] != '(' \
		&& tokens[tempi][0] != '&' && tokens[tempi][0] != ')')
	{
		if ((tokens[tempi] && (tokens[tempi][0] == '>' \
					|| tokens[tempi][0] == '<')) || (tokens[tempi] && tempi > 0 \
				&& (tokens[tempi - 1][0] == '>' || tokens[tempi \
					- 1][0] == '<')))
			arg_count--;
		arg_count++;
		tempi++;
	}
	args = ft_calloc(arg_count + 1, sizeof(char *));
	what_about_args(tokens, i, args);
	return (add_new_cmd(cmd, args, arg_count, ast_cmd));
}
