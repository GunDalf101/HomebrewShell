/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlektaib <mlektaib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 21:21:23 by mlektaib          #+#    #+#             */
/*   Updated: 2023/05/11 18:57:47 by mlektaib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.h"
#include <stdio.h>

int	to_home_dir(t_env **env)
{
	char	*path;

	path = NULL;
	path = ft_strjoin("/Users/", get_env(*env, "USER")->value);
	if (get_env(*env, "OLDPWD"))
		exportadd_for_cd(env, envnew("OLDPWD", return_pwd(), 0));
	if (chdir(path) == 0)
	{
		free(path);
		return (0);
	}
	else
		return (1);
}

int	to_prev_dir(t_env **env)
{
	char	*path;

	path = NULL;
	if (get_env(*env, "OLDPWD"))
		path = get_env(*env, "OLDPWD")->value;
	if (!path)
	{
		ft_putendl_fd("bash: cd: OLDPWD not set", 2);
		return (1);
	}
	if (chdir(path) == 0)
	{
		exportadd_for_cd(env, envnew("OLDPWD", return_pwd(), 0));
		return (0);
	}
	else
		return (1);
}

int	to_dir(t_ast *node, t_env **env)
{
	char	*path;

	if (get_env(*env, "OLDPWD"))
		path = get_env(*env, "OLDPWD")->value;
	if (chdir(node->u_data.cmd.args[1]) == 0)
	{
		if (get_env(*env, "OLDPWD"))
			exportadd_for_cd(env, envnew("OLDPWD", path, 0));
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

int	cd(t_ast *node, t_env **env)
{
	if (!node->u_data.cmd.args[1])
		return (0);
	else
	{
		if (!strcmp(node->u_data.cmd.args[1], "~"))
			return (to_home_dir(env));
		else if (!strcmp(node->u_data.cmd.args[1], "-"))
			return (to_prev_dir(env));
		else
			return (to_dir(node, env));
	}
	if (get_env(*env, "PWD"))
		exportadd_for_cd(env, envnew("PWD", return_pwd(), 0));
	return (1);
}
