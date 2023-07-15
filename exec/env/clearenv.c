/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clearenv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlektaib <mlektaib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 14:42:06 by mlektaib          #+#    #+#             */
/*   Updated: 2023/07/15 06:15:53 by mlektaib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

void	ft_clearenv(t_env **head)
{
	t_env	*tmp;

	while (*head)
	{
		tmp = *head;
		*head = (*head)->next;
		free(tmp->key);
		if (tmp->value)
			free(tmp->value);
		free(tmp);
	}
	free(*head);
}

void	key_value_helper2(t_argtoenv *var)
{
	if (!var->value && var->found)
		envadd_back(&var->head, envnew(ft_strdup(var->key),
				ft_strdup(""), var->k), 0);
	else if (!var->value)
		envadd_back(&var->head, envnew(ft_strdup(var->key), NULL, var->k), 0);
	else if (var->found)
		envadd_back(&var->head, envnew(ft_strdup(var->key),
				ft_strdup(var->value), var->k), 0);
}

void	key_value_helper(t_argtoenv *var, char *env)
{
	var->key = env;
	var->found = 0;
	var->k = 0;
	while (var->key[var->i2] != '=' && var->key[var->i2] != '\0')
			var->i2++;
	if (var->key[var->i2] == '=')
	{
		var->value = &var->key[var->i2 + 1];
		var->found = 1;
	}
	if (var->key[0] != '=')
		var->key[var->i2] = '\0';
	if (var->key[ft_strlen(var->key) - 1] == '+' && var->found == 1)
	{
		var->key[ft_strlen(var->key) - 1] = 0;
		var->k = 1;
	}
	key_value_helper2(var);
}

void	argtoenv_init(t_argtoenv *var)
{
	var->head = NULL;
	var->keyvalue = NULL;
	var->d = 0;
	var->k = 0;
	var->i = 0;
	var->i2 = 0;
	var->found = 0;
	var->key = NULL;
	var->value = NULL;
}

void	replace_env_node(t_env *tmp, t_env *new)
{
	char	*tmpvalue;

	tmpvalue = NULL;
	tmpvalue = tmp->value;
	if (new->value)
	{
		tmp->value = new->value;
		free(tmpvalue);
	}
	free(new->key);
	free(new);
}
