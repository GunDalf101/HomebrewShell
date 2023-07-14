/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlektaib <mlektaib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 21:21:40 by mlektaib          #+#    #+#             */
/*   Updated: 2023/07/14 01:00:17 by mlektaib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.h"

void	freeenvnode(t_env *tmp)
{
	free(tmp->key);
	free(tmp->value);
	free(tmp);
}

int	delete_env(t_env *deleted, t_env *tmp, t_env *prev, t_env **head)
{
	if (ft_strcmp("PWD", deleted->key) == 0 && get_env(*head, "PWD"))
	{
		get_env(*head, "PWD")->hidden = 1;
		return (0);
	}
	else if (ft_strcmp("HOME", deleted->key) == 0 && get_env(*head, "USER"))
	{
		get_env(*head, "HOME")->hidden = 1;
		return (0);
	}
	else if (ft_strcmp(tmp->key, deleted->key) == 0)
	{
		if (prev == NULL)
			*head = tmp->next;
		else
			prev->next = tmp->next;
		freeenvnode(tmp);
		return (1);
	}
	return (0);
}

int	unsetcmd(t_env **head, t_ast *node)
{
	t_env	*tmp;
	t_env	*tmp2;
	t_env	*prev;
	t_env	*deleted;

	if (!node->u_data.cmd.args[1])
		exportcmd(*head);
	deleted = key_value_to_list(node->u_data.cmd.args + 1);
	tmp2 = deleted;
	while (deleted)
	{
		prev = NULL;
		tmp = *head;
		while (tmp)
		{
			if (delete_env(deleted, tmp, prev, head))
				break ;
			prev = tmp;
			tmp = tmp->next;
		}
		deleted = deleted->next;
	}
	free_env_lst(tmp2);
	return (0);
}

int	_unsetenv(char *deleted, t_env **head)
{
	t_env	*tmp;
	t_env	*prev;

	if (!*head)
		return (0);
	tmp = *head;
	prev = NULL;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, deleted) == 0)
		{
			if (prev == NULL)
				*head = tmp->next;
			else
				prev->next = tmp->next;
			freeenvnode(tmp);
			return (1);
		}
		prev = tmp;
		tmp = tmp->next;
	}
	return (0);
}
