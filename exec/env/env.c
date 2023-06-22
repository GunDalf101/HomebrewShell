/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlektaib <mlektaib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 21:21:01 by mlektaib          #+#    #+#             */
/*   Updated: 2023/06/22 16:15:34 by mlektaib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include <string.h>

t_env	*key_value_to_list(char **env)
{
	t_argtoenv var;
	
	argtoenv_init(&var);
	while (env[var.i] != NULL)
	{
		var.k = 0;
		var.keyvalue = NULL;
		key_value_helper(&var,env);
		free(var.keyvalue);
		var.i++;
	}
	return (var.head);
}

t_env	*envnew(char *key, char *value, int append)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->key = key;
	new->value = value;
	new->append = append;
	new->next = NULL;
	return (new);
}

void	envadd_back(t_env **head, t_env *node,int hidden)
{
	t_env	*tmp;

	if (!head)
		return ;
	tmp = *head;
	if (*head == NULL)
		*head = node;
	else
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = node;
	}
	node->hidden = hidden;
	node->next = NULL;
}

t_env	*load_env(char **env)
{
	t_env	*head;
	char	*key;
	char	*value;
	int		i;
	char	*tmp;

	head = NULL;
	i = 0;
	while (*env)
	{
		key = NULL;
		value = NULL;
		i = 0;
		tmp = strdup(*env);
		key = tmp;
		while (tmp[i] != '=' && tmp[i] != '\0')
			i++;
		if (tmp[i] == '=')
			value = &tmp[i + 1];
		tmp[i] = '\0';
		envadd_back(&head, envnew(ft_strdup(key), ft_strdup(value), 0), 0);
		free(tmp);
		env++;
	}
	return (head);
}

t_env	*get_env(t_env *head, char *env)
{
	t_env	*tmp;

	tmp = head;
	if (!env)
		return (0);
	while (tmp)
	{
		if (!strcmp(tmp->key, env))
			return (tmp);
		tmp = tmp->next;
	}
	return (0);
}
