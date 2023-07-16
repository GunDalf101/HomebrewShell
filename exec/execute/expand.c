/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlektaib <mlektaib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 23:01:38 by mlektaib          #+#    #+#             */
/*   Updated: 2023/07/16 05:11:15 by mlektaib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

extern t_global	g_global;

void	expand_intialize(t_expand *expand, char *str)
{
	expand->str = str;
	expand->i = 0;
	expand->j = 0;
	expand->len = ft_strlen(str);
	expand->inside_single = FALSE;
	expand->inside_double = FALSE;
	expand->start = 0;
	expand->end = 0;
	expand->value = NULL;
	expand->var = NULL;
	expand->s = 0;
}

void	expand_start(t_expand *expand, t_env *env)
{
	expand->start = expand->i;
	expand->i++;
	while (expand->str[expand->i] && (ft_isalnum(expand->str[expand->i])
			|| expand->str[expand->i] == '_'))
		expand->i++;
	if (expand->str[expand->i] == '?')
		expand->i++;
	expand->end = expand->i;
	if (expand->end - expand->start > 1)
		expand_end(expand, env);
	else
		expand->i--;
}

char	*quotes_busters(char *str, t_env *env, int flag)
{
	t_expand	expand;

	expand_intialize(&expand, str);
	while (expand.i < expand.len)
	{
		if (expand.str[expand.i] == '\'' && !expand.inside_double)
			expand.inside_single = !expand.inside_single;
		else if (expand.str[expand.i] == '"' && !expand.inside_single)
			expand.inside_double = !expand.inside_double;
		if (!expand.inside_single)
			if (expand.str[expand.i] == '$' && !flag)
				expand_start(&expand, env);
		if (expand.str[expand.i] && (expand.str[expand.i] != '\''
				|| expand.inside_double || expand.str[expand.i] != '"'
				|| expand.inside_single))
			expand.str[expand.j++] = expand.str[expand.i];
		expand.i++;
	}
	expand.len = ft_strlen(expand.str);
	if (flag == 1)
		expand.str = quotes_remover(expand.str);
	if (expand.len == 0)
		return (free(expand.str), NULL);
	expand.str[expand.j] = '\0';
	return (expand.str);
}

t_ast	*expand(t_ast *node, t_env **env)
{
	if (node)
		node = expander(node, env, 0);
	if (node)
		wildcard_dealer(node);
	if (node)
		node = expander(node, env, 1);
	return (node);
}

t_ast	*expander(t_ast *node, t_env **env, int f)
{
	if (!node->u_data.cmd.cmd)
		return (node);
	if (node->type == ast_cmd || node->type == ast_imp)
	{
		expand_command(node, env, f);
		rebuild_cmd_node(node, env, f);
		if (node->u_data.cmd.cmd == NULL && node->u_data.cmd.args[0])
			node->u_data.cmd.cmd = ft_strdup(node->u_data.cmd.args[0]);
	}
	return (node);
}
