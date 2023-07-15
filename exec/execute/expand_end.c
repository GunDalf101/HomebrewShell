/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_end.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlektaib <mlektaib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 08:56:27 by mlektaib          #+#    #+#             */
/*   Updated: 2023/07/15 11:19:38 by mlektaib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

extern t_global	g_global;

void	expand_end(t_expand *expand, t_env *env)
{
	expand->var = ft_substr(expand->str, expand->start + 1, expand->end \
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
	quote_on_quote(expand);
	free(expand->var);
	free(expand->value);
}
