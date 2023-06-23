/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clearenv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlektaib <mlektaib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 14:42:06 by mlektaib          #+#    #+#             */
/*   Updated: 2023/06/23 14:22:54 by mlektaib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

void	clearenv(t_env **head)
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

void	key_value_helper(t_argtoenv *var, char *env)
{
	int i = 0;
	char *key;
	char *value;
	int found;

	key = env;
	value = NULL;
	found = 0;
	while (key[i] != '=' && key[i] != '\0')
			i++;
	if (key[i] == '=')
	{
		value = &key[i + 1];
		found = 1;
	}
	key[i] = '\0';
	if (key[ft_strlen(key) - 1] == '+')
	{
		key[ft_strlen(key) - 1] = 0;
		var->k = 1;
	}
	if (!value && found)
		envadd_back(&var->head, envnew(ft_strdup(key), ft_strdup(""), var->k),
			0);
	else if (!value)
		envadd_back(&var->head, envnew(key, NULL, var->k), 0);
	else if(found)
		envadd_back(&var->head, envnew(ft_strdup(key), ft_strdup(value),
				var->k), 0);
}

void	argtoenv_init(t_argtoenv *var)
{
	var->head = NULL;
	var->keyvalue = NULL;
	var->d = 0;
	var->k = 0;
	var->i = 0;
}
