/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlektaib <mlektaib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 21:21:35 by mlektaib          #+#    #+#             */
/*   Updated: 2023/04/10 03:18:46 by mlektaib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.h"
#include <stdio.h>

int	exportcmd(t_env *head)
{
	int		size;
	char	**env;
	int		i;

	size = lstsize(head);
	env = lst_to_env(head);
	sort_env(env, size);
	i = 0;
	while (i < size)
	{
		ft_putendl_fd(env[i], 1);
		i++;
	}
	free_env(env, size);
	return (0);
}

void	display_export_error(t_env *new, int *k)
{
	ft_putstr_fd("bash: export: ", 1);
	ft_putstr_fd("\'", 1);
	ft_putstr_fd(new->key, 1);
	ft_putstr_fd("=", 1);
	ft_putstr_fd(new->value, 1);
	ft_putstr_fd("\'", 1);
	ft_putendl_fd(": not a valid identifier", 1);
	free(new->key);
	free(new->value);
	free(new);
	*k = 1;
}

void	add_to_env(t_env **head, t_env *new)
{
	t_env	*tmp;
	char	*tmpvalue;

	tmp = get_env(*head, new->key);
	if (!tmp)
		envadd_back(head, new);
	else if (new->append == 0)
	{
		tmpvalue = tmp->value;
		tmp->value = new->value;
		free(tmpvalue);
		free(new->key);
		free(new);
	}
	else if (new->append == 1)
	{
		tmpvalue = tmp->value;
		tmp->value = ft_strjoin(tmp->value, new->value);
		free(tmpvalue);
		free(new->value);
		free(new->key);
		free(new);
	}
}

int	exportadd(t_env **head, t_ast *node)
{
	int		k;
	t_env	*new;
	// t_env	*newhead;
	t_env	*prenext;

	k = 0;
	if (!node->u_data.cmd.args[1])
		return (exportcmd(*head));
	new = key_value_to_list(node->u_data.cmd.args + 1);
	// newhead = new;
	while (new)
	{
		prenext = new->next;
		if (check_key(new->key))
			add_to_env(head, new);
		else
			display_export_error(new, &k);
		new = prenext;
	}
	return (k);
}

int	exportadd_for_cd(t_env **head, t_env *new)
{
	int		k;
	t_env	*tmp;

	k = 0;
	while (new)
	{
		if (check_key(new->key))
		{
			tmp = get_env(*head, new->key);
			if (!tmp)
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
