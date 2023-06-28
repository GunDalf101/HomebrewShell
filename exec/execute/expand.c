/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbennani <mbennani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 23:01:38 by mlektaib          #+#    #+#             */
/*   Updated: 2023/06/24 23:55:27 by mbennani         ###   ########.fr       */
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
	{
		expand->var = ft_substr(expand->str, expand->start + 1, expand->end
				- expand->start - 1);
		expand->value = NULL;
		if (expand->var[0] == '?')
			expand->value = ft_itoa(g_global.exit_status);
		else if (get_env(env, expand->var))
			expand->value = ft_strdup(get_env(env, expand->var)->value);
		else
			expand->value = ft_strdup("");
		if (expand->value)
			replace_env(expand);
		free(expand->var);
		free(expand->value);
	}
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
			if (expand.str[expand.i] == '$')
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

void	args_remake(t_ast *node)
{
	char				**newargs;
	char				**fullargs;
	int					count;
	t_quote_parenthesis	*quotes;

	quotes = malloc(sizeof(t_quote_parenthesis	*));
	count = 0;
	newargs = split_with_a_twist(node->u_data.cmd.cmd, ' ', quotes);
	while (newargs[count])
		count++;
	free(node->u_data.cmd.cmd);
	node->u_data.cmd.cmd = ft_strdup(newargs[0]);
	fullargs = ft_calloc(count + node->u_data.cmd.arg_count, sizeof(char *));
	count = 0;
	int k = 0;
	while (newargs[k])
	{
		fullargs[count] = ft_strdup(newargs[k]);
		free(newargs[k]);
		count++;
		k++;
	}
	free(newargs);
	k = 1;
	while (node->u_data.cmd.args[k])
	{
		fullargs[count] = ft_strdup(node->u_data.cmd.args[k]);
		count++;
		k++;
	}
	fullargs[count] = NULL;
	node->u_data.cmd.args = ft_calloc(count, sizeof(char *));
	count = 0;
	while (fullargs[count])
	{
		node->u_data.cmd.args[count] = ft_strdup(fullargs[count]);
		free(fullargs[count]);
		count++;
	}
	free(fullargs);
	node->u_data.cmd.args[count] = NULL;
}

t_ast	*expander(t_ast *node, t_env **env, int f)
{
	int		i;
	t_quote_parenthesis	*quotes;

	quotes = malloc(sizeof(t_quote_parenthesis	*));
	if (node->type == ast_cmd || node->type == ast_imp)
	{
		i = 0;
		node->u_data.cmd.cmd = quotes_busters(node->u_data.cmd.cmd, *env, f);
		while (node->u_data.cmd.cmd[i] && f == 0)
		{
			super_quote_hander(quotes, node->u_data.cmd.cmd[i]);
			if (node->u_data.cmd.cmd[i] == ' ' && quotes->dubquo == FALSE && quotes->sinquo == FALSE)
			{
				args_remake(node);
				break ;
			}
			i++;
		}
		i = 0;
		while (node->u_data.cmd.args[i])
		{
			node->u_data.cmd.args[i] = quotes_busters(node->u_data.cmd.args[i],
					*env, f);
			if (node->u_data.cmd.args[i] == NULL && node->u_data.cmd.args[i
					+ 1])
			{
				shift_args(node, i);
				i = 0;
			}
			i++;
		}
		if (node->u_data.cmd.cmd == NULL)
			node->u_data.cmd.cmd = ft_strdup(node->u_data.cmd.args[0]);
	}
	return (node);
}
