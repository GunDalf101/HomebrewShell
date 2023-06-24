/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlektaib <mlektaib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 11:40:53 by mlektaib          #+#    #+#             */
/*   Updated: 2023/06/24 11:51:37 by mlektaib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.h"

void	export_init(t_export *vars, t_env *head)
{
	vars->i = 0;
	vars->l = 0;
	vars->key = NULL;
	vars->value = NULL;
	vars->size = lstsize(head);
	vars->env = lst_to_env(head);
}

void	free_env_node(t_env *new, char *tmpvalue)
{
	free(tmpvalue);
	free(new->value);
	free(new->key);
	free(new);
}
