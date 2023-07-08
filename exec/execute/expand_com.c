/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_com.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbennani <mbennani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 13:47:11 by mbennani          #+#    #+#             */
/*   Updated: 2023/07/08 14:24:59 by mbennani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

char	**create_fullargs_array(char **newargs, int arg_count)
{
	char	**fullargs;
	int		count;
	int		k;

	fullargs = ft_calloc(arg_count, sizeof(char *));
	count = 0;
	k = 0;
	while (newargs[k])
	{
		fullargs[count] = ft_strdup(newargs[k]);
		free(newargs[k]);
		count++;
		k++;
	}
	free(newargs);
	return (fullargs);
}

void	append_remaining_args(t_ast *node, char **fullargs, int count)
{
	int	k;

	k = 1;
	while (node->u_data.cmd.args[k])
	{
		fullargs[count] = ft_strdup(node->u_data.cmd.args[k]);
		free(node->u_data.cmd.args[k]);
		count++;
		k++;
	}
	free(node->u_data.cmd.args[0]);
	free(node->u_data.cmd.args);
	node->u_data.cmd.args = fullargs;
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
