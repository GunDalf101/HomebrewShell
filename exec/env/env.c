/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlektaib <mlektaib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 21:21:01 by mlektaib          #+#    #+#             */
/*   Updated: 2023/05/11 15:17:16 by mlektaib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include <string.h>

t_env	*key_value_to_list(char **env)
{
	t_env	*head;
	char	**keyvalue;
	int		d;
	int		k;

	head = NULL;
	k = 0;
	while (*env != NULL)
	{
		k = 0;
		keyvalue = ft_split(*env, '=');
		d = ft_strlen(keyvalue[0]) - 1;
		if (keyvalue[0][d] == '+')
		{
			keyvalue[0] = append_env_mode(keyvalue[0], &k);
		}
		if (!keyvalue[1])
			envadd_back(&head, envnew(keyvalue[0], ft_strdup(""), k));
		else
			envadd_back(&head, envnew(keyvalue[0], keyvalue[1], k));
		free(keyvalue);
		env++;
	}
	return (head);
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

void	envadd_back(t_env **head, t_env *node)
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
		envadd_back(&head, envnew(key, value, 0));
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
		if (strcmp(tmp->key, env) == 0)
			return (tmp);
		tmp = tmp->next;
	}
	return (0);
}