/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_remaster.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlektaib <mlektaib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 14:19:58 by mbennani          #+#    #+#             */
/*   Updated: 2023/07/13 00:14:05 by mlektaib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

void	quote_on_quote(t_expand *expand)
{
	if (expand->str[expand->i] == '\'' && !expand->inside_double)
		expand->inside_single = !expand->inside_single;
	else if (expand->str[expand->i] == '"' && !expand->inside_single)
		expand->inside_double = !expand->inside_double;
}

void	update_command(t_ast *node, char *command)
{
	free(node->u_data.cmd.cmd);
	node->u_data.cmd.cmd = ft_strdup(command);
}

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

void	rebuild_cmd_node(t_ast *node, t_env **env, int f)
{
	int	i;

	i = 0;
	while (i < node->u_data.cmd.arg_count)
	{
		if (node->u_data.cmd.args[i])
		{
			node->u_data.cmd.args[i] = quotes_busters(node->u_data.cmd.args[i], \
			*env, f);
			if (node->u_data.cmd.args[i] == NULL)
			{
				shift_args(node, i);
				i = 0;
				continue ;
			}
		}
		i++;
	}
}
