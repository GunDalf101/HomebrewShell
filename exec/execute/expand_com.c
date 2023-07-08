/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_com.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbennani <mbennani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 13:47:11 by mbennani          #+#    #+#             */
/*   Updated: 2023/07/08 14:57:54 by mbennani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

t_quote_parenthesis	*initialize_quotes(void)
{
	t_quote_parenthesis	*quotes;

	quotes = ft_calloc(sizeof(t_quote_parenthesis *), 1);
	return (quotes);
}

char	**split_command_with_quotes(t_ast *node, t_quote_parenthesis *quotes)
{
	char	**newargs;

	newargs = split_with_a_twist(node->u_data.cmd.cmd, ' ', quotes);
	return (newargs);
}

void	update_arg_count(t_ast *node)
{
	int	count;

	count = 0;
	while (node->u_data.cmd.args[count])
		count++;
	node->u_data.cmd.arg_count = count;
}

void	args_remake(t_ast *node)
{
	t_quote_parenthesis	*quotes;
	char				**newargs;
	int					count;
	char				**fullargs;

	quotes = initialize_quotes();
	newargs = split_command_with_quotes(node, quotes);
	count = 0;
	while (newargs[count])
		count++;
	update_command(node, newargs[0]);
	fullargs = create_fullargs_array(newargs, count \
		+ node->u_data.cmd.arg_count);
	append_remaining_args(node, fullargs, count);
	update_arg_count(node);
	free(quotes);
}

void	expand_command(t_ast *node, t_env **env, int f)
{
	t_quote_parenthesis	*quotes;
	int					i;

	i = 0;
	quotes = ft_calloc(sizeof(t_quote_parenthesis *), 1);
	node->u_data.cmd.cmd = quotes_busters(node->u_data.cmd.cmd, *env, f);
	if (node->u_data.cmd.cmd)
	{
		while (node->u_data.cmd.cmd[i] && f == 0)
		{
			super_quote_hander(quotes, node->u_data.cmd.cmd[i]);
			if (node->u_data.cmd.cmd[i] == ' ' && quotes->dubquo == FALSE
				&& quotes->sinquo == FALSE)
			{
				args_remake(node);
				break ;
			}
			i++;
		}
	}
	free(quotes);
}
