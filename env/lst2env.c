/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst2env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlektaib <mlektaib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 21:21:04 by mlektaib          #+#    #+#             */
/*   Updated: 2023/04/08 21:21:05 by mlektaib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

char	**lst_to_env(t_env *head)
{
	size_t size =lstsize(head);
	char **envs = malloc(size * sizeof(char *)+1);
	t_env *current = head;
	int i = 0;

	while (current != NULL)
	{
		char *env = ft_strjoin(current->key, "=");
		env = ft_strjoin(env, current->value);
		envs[i] = env;
		i++;
		current = current->next;
	}
	envs[i] = NULL;
	return (envs);
}

int	lstsize(t_env *head)
{
	t_env	*tmp;
	int		i;

	i = 0;
	tmp = head;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}