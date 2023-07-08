/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_remaster.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbennani <mbennani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 14:19:58 by mbennani          #+#    #+#             */
/*   Updated: 2023/07/08 14:25:21 by mbennani         ###   ########.fr       */
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

void	update_command(t_ast *node, char *command)
{
	free(node->u_data.cmd.cmd);
	node->u_data.cmd.cmd = ft_strdup(command);
}
