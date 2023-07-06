/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlektaib <mlektaib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 21:21:35 by mlektaib          #+#    #+#             */
/*   Updated: 2023/07/06 13:24:18 by mlektaib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.h"
#include <stdio.h>

int	exportcmd(t_env *head)
{
	t_export	vars;

	export_init(&vars, head);
	sort_env(vars.env, vars.size);
	while (vars.env[vars.i])
	{
		ft_putstr_fd("declare -x ", 1);
		vars.l = 0;
		while (vars.env[vars.i][vars.l] && vars.env[vars.i][vars.l] != '=')
			vars.l++;
		vars.key = vars.env[vars.i];
		vars.env[vars.i][vars.l] = 0;
		vars.value = &vars.env[vars.i][vars.l + 1];
		ft_putstr_fd(vars.key, 1);
		if (vars.value[0] != '\0')
			printf("=\"%s\"\n", vars.value);
		else
			printf("\n");
		vars.i++;
	}
	free_env(vars.env, vars.size);
	return (0);
}

void	display_export_error(t_env *new, int *k)
{
	ft_putstr_fd("bash: export: ", 1);
	ft_putstr_fd("\'", 1);
	ft_putstr_fd(new->key, 1);
	if (ft_strlen(new->value))
	{
		ft_putstr_fd("=", 1);
		ft_putstr_fd(new->value, 1);
	}
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
		envadd_back(head, new, 0);
	else if (new->append == 0)
	{
		tmpvalue = tmp->value;
		if (new->value)
		{
			tmp->value = new->value;
			free(tmpvalue);
		}
		free(new->key);
		free(new);
	}
	else if (new->append == 1)
	{
		tmpvalue = tmp->value;
		tmp->value = ft_strjoin(tmp->value, new->value);
		free_env_node(new, tmpvalue);
	}
}

int	exportadd(t_env **head, t_ast *node)
{
	int		k;
	t_env	*new;
	t_env	*prenext;

	k = 0;
	if (!node->u_data.cmd.args[1])
		return (exportcmd(*head));
	new = key_value_to_list(node->u_data.cmd.args + 1);
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
	t_env	*tmp;
	char	*tmpvalue;

	tmp = get_env(*head, new->key);
	if (!tmp)
		envadd_back(head, new, 0);
	else if (new->append == 0)
	{
		tmpvalue = tmp->value;
		if (new->value)
		{
			tmp->value = new->value;
			free(tmpvalue);
		}
		free(new);
	}
	return (0);
}
