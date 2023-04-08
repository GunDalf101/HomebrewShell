/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlektaib <mlektaib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 21:21:35 by mlektaib          #+#    #+#             */
/*   Updated: 2023/04/08 21:21:36 by mlektaib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.h"
#include <stdio.h>
int	assign_ranks(t_env *head)
{
	t_env	*temp;
	int		size;
	t_env	**arr;
	t_env	*tmp;
	int		rank;

	temp = head;
	size = lstsize(head);
	int l = 0;
	arr = malloc(sizeof(t_env *));
	while(l < size)
	{
		arr[l] = malloc(sizeof(t_env));
		l++;
	}
	temp = head;
	for (int i = 0; i < size; i++)
	{
		arr[i] = temp;
		temp = temp->next;
	}
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size - i - 1; j++)
		{
			if (strcmp(arr[j]->key, arr[j + 1]->key) > 0)
			{
				tmp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = tmp;
			}
		}
	}
	rank = 1;
		

	for (int i = 0; i < size; i++)
	{
		arr[i]->rank = rank;
		if (i < size - 1 && strcmp(arr[i]->key, arr[i + 1]->key) < 0)
		{
			rank++;
		}
	}
	return (size);
}

int	exportcmd(t_env *head)
{
	int		size;
	t_env	*tmp;
	int		i;

	
	size = assign_ranks(head);
	tmp = head;
	i = 1;
	while (i <= size)
	{
		if (tmp->rank == i)
		{
			ft_putstr_fd("declare -x ", 1);
			ft_putstr_fd(tmp->key, 1);
			ft_putstr_fd("=", 1);
			ft_putstr_fd("\"", 1);
			ft_putstr_fd(tmp->value, 1);
			ft_putstr_fd("\"\n", 1);
			i++;
			tmp = head;
		}
		tmp = tmp->next;
		if (!tmp)
			tmp = head;
	}
	return (0);
}
int	exportadd(t_env **head,t_ast *node)
{
	int k = 0;
	t_env *tmp;
	if(!node->u_data.cmd.args[1])
		exportcmd(*head);
	t_env *new = key_value_to_list(node->u_data.cmd.args+1);
	while (new)
	{
		if (check_key(new->key))
		{
			tmp = get_env(*head,new->key);
			if(!tmp)
				envadd_back(head, new);
			else if( new->append == 0)
					tmp->value = new->value;
			else if( new->append == 1)
				tmp->value = ft_strjoin(tmp->value,new->value);
		}
		else
		{
			ft_putstr_fd("bash: export: ",1);
			ft_putstr_fd("\'",1);
			ft_putstr_fd(new->key, 1);
			ft_putstr_fd("=", 1);
			ft_putstr_fd(new->value, 1);
			ft_putstr_fd("\'",1);
			ft_putendl_fd(": not a valid identifier",1);
			k = 1;
		}
		new = new->next;
	}
	return k;
}
int	exportadd_for_cd(t_env **head, t_env *new)
{
	int k = 0;
	t_env *tmp;
	while (new)
	{
		if (check_key(new->key))
		{
			tmp = get_env(*head,new->key);
			if(!tmp)
				envadd_back(head, new);
			else
					tmp->value = new->value;
		}
		else
			k = 1;
		new = new->next;
	}

	return (k);
}