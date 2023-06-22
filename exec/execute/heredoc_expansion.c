/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expansion.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbennani <mbennani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 23:02:19 by mlektaib          #+#    #+#             */
/*   Updated: 2023/06/22 21:14:45 by mbennani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

extern t_global	g_global;

char	*heredoc_expansion(char *str, t_env *env)
{
	t_expand	expand;

	expand_intialize(&expand, str);
	while (expand.str[expand.i])
	{
		if (str[expand.i] == '$')
			expand_start(&expand, env);
		expand.i++;
	}
	return (expand.str);
}

char	*quotes_remover(char *str)
{
	t_expand	var;

	expand_intialize(&var, str);
	var.s = 0;
	while (var.str[var.s] && var.str[var.s] != '\'' && var.str[var.s] == '\"')
		var.s++;
	if (!var.str[var.s])
		return (var.str);
	while (var.i < var.len)
	{
		if (var.str[var.i] == '\'' && !var.inside_double)
			var.inside_single = !var.inside_single;
		else if (var.str[var.i] == '"' && !var.inside_single)
			var.inside_double = !var.inside_double;
		else
			var.str[var.j++] = var.str[var.i];
		var.i++;
	}
	var.str[var.j] = '\0';
	return (var.str);
}

void	replace_env(t_expand *expand)
{
	char *firstpart;
	char *secondpart;
	char *new_str;

	firstpart = ft_substr(expand->str, 0, expand->start);
	secondpart = ft_substr(expand->str, expand->end, expand->len - expand->end);
	new_str = ft_strjoin(firstpart, expand->value);
	free(firstpart);
	free(expand->str);
	expand->str = ft_strjoin(new_str, secondpart);
	free(secondpart);
	free(new_str);
	expand->len = ft_strlen(expand->str);
	expand->i = expand->start + ft_strlen(expand->value);
	expand->j = expand->i;
}