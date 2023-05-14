/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlektaib <mlektaib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 21:21:40 by mlektaib          #+#    #+#             */
/*   Updated: 2023/04/09 22:32:54 by mlektaib         ###   ########.fr       */
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
	if (strcmp(tmp->key, deleted->key) == 0)
	{
		if (prev == NULL)
			*head = tmp->next;
		else
		{
			prev->next = tmp->next;
		}
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