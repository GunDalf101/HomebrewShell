/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   astV2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbennani <mbennani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 04:30:46 by mbennani          #+#    #+#             */
/*   Updated: 2023/06/22 04:33:44 by mbennani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing101.h"
#include "ast.h"

t_ast	*add_new_cmd(char *cmd, char **args, int arg_count,
		enum e_ast_type type)
{
	t_ast	*node;
	int		i;

	node = malloc(sizeof(t_ast));
	if (!node)
		return (NULL);
	node->type = type;
	node->u_data.cmd.cmd = ft_strdup(cmd);
	free(cmd);
	node->u_data.cmd.args = malloc(sizeof(char *) * (arg_count + 1));
	i = 0;
	while (i < arg_count && args[i])
	{
		node->u_data.cmd.args[i] = ft_strdup(args[i]);
		free(args[i]);
		i++;
	}
	free(args);
	node->u_data.cmd.args[i] = NULL;
	node->u_data.cmd.arg_count = arg_count;
	return (node);
}
