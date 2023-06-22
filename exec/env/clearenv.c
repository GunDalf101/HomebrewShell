/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clearenv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbennani <mbennani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 14:42:06 by mlektaib          #+#    #+#             */
/*   Updated: 2023/06/22 21:16:43 by mbennani         ###   ########.fr       */
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

void	key_value_helper(t_argtoenv *var, char **env)
{
	if (env[var->i][0] != '=' || !env[var->i][0])
		var->keyvalue = ft_split(env[var->i], '=');
	else
	{
		var->keyvalue = malloc(sizeof(char *) * 2);
		var->keyvalue[0] = ft_strdup(env[var->i]);
		var->keyvalue[1] = ft_strdup("");
	}
	var->d = ft_strlen(var->keyvalue[0]) - 1;
	if (var->keyvalue[0][var->d] == '+')
		var->keyvalue[0] = append_env_mode(var->keyvalue[0], &var->k);
	if (!var->keyvalue[1] && env[var->i][ft_strlen(env[var->i]) - 1] == '=')
		envadd_back(&var->head, envnew(var->keyvalue[0], ft_strdup(""), var->k),
			0);
	else if (!var->keyvalue[1])
		envadd_back(&var->head, envnew(var->keyvalue[0], NULL, var->k), 0);
	else
		envadd_back(&var->head, envnew(var->keyvalue[0], var->keyvalue[1],
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