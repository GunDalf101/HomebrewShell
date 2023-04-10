/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlektaib <mlektaib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 21:21:23 by mlektaib          #+#    #+#             */
/*   Updated: 2023/04/10 01:55:57 by mlektaib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.h"
#include <stdio.h>

int	cd(t_ast *node, t_env **env)
{
	char *path = NULL;
	if (!node->u_data.cmd.args[1])
		return (0);
	else
	{
		if (!strcmp(node->u_data.cmd.args[1], "~"))
		{
			path = ft_strjoin("/Users/", get_env(*env, "USER")->value);
			if (get_env(*env, "OLDPWD"))
				exportadd_for_cd(env, envnew("OLDPWD", return_pwd(), 0));
			if (chdir(path) == 0)
			{
				free(path);
				return (0);
			}
		}
		else if (!strcmp(node->u_data.cmd.args[1], "-"))
		{
			if (get_env(*env, "OLDPWD"))
				path = get_env(*env, "OLDPWD")->value;
			if (!path)
			{
				printf("dfsafd\n");
				ft_putendl_fd("bash: cd: OLDPWD not set", 2);
			}
			else if (chdir(path) == 0)
			{
				exportadd_for_cd(env, envnew("OLDPWD", return_pwd(), 0));
				return (0);
			}
		}
		else
		{
			if (chdir(node->u_data.cmd.args[1]) == 0)
			{
				if (get_env(*env, "OLDPWD"))
					exportadd_for_cd(env, envnew("OLDPWD", return_pwd(), 0));
				return (0);
			}
			else
			{
				ft_putstr_fd("bash: cd: ", 2);
				ft_putstr_fd(node->u_data.cmd.args[1], 2);
				ft_putstr_fd(": ", 2);
				perror("");
				return (1);
			}
		}
	}
	if (get_env(*env, "PWD"))
		exportadd_for_cd(env, envnew("PWD", return_pwd(), 0));
	return (1);
}
