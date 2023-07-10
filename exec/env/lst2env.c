/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst2env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlektaib <mlektaib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 21:21:04 by mlektaib          #+#    #+#             */
/*   Updated: 2023/07/10 11:44:42 by mlektaib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

void	free_env_lst(t_env *head)
{
	t_env	*temp;

	if (head)
	{
		while (head)
		{
			temp = head->next;
			free(head->key);
			free(head->value);
			free(head);
			head = temp;
		}
	}
}

char	**lst_to_env(t_env *head)
{
	t_lstenv	var;

	var.size = lstsize(head);
	var.envs = malloc(var.size * sizeof(char *) + 1);
	var.i = 0;
	while (var.i < (int)var.size)
	{
		if (head->hidden == 0)
		{
			if (head->value != NULL)
			{
				var.tmp = ft_strjoin(head->key, "=");
				var.env = ft_strjoin(var.tmp, head->value);
				free(var.tmp);
			}
			else
				var.env = ft_strdup(head->key);
			var.envs[var.i] = var.env;
			var.i++;
		}
		head = head->next;
	}
	var.envs[var.i] = NULL;
	return (var.envs);
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

void	load_env_init(t_loadenv *var)
{
	var->head = NULL;
	var->key = NULL;
	var->value = NULL;
	var->i = 0;
	var->tmp = NULL;
	var->found = 0;
}

void	load_helper(t_loadenv *var, char **env)
{
	while (*env)
	{
		var->found = 0;
		var->key = NULL;
		var->value = NULL;
		var->i = 0;
		var->tmp = ft_strdup(*env);
		var->key = var->tmp;
		while (var->tmp[var->i] != '=' && var->tmp[var->i] != '\0')
			var->i++;
		if (var->tmp[var->i] == '=')
		{
			var->found = 1;
			var->value = &var->tmp[var->i + 1];
		}
		var->tmp[var->i] = '\0';
		if (var->found)
			envadd_back(&var->head, envnew(ft_strdup(var->key),
					ft_strdup(var->value), 0), 0);
		else
			envadd_back(&var->head, envnew(ft_strdup(var->key),
					ft_strdup(""), 0), 0);
		free(var->tmp);
		env++;
	}
}
