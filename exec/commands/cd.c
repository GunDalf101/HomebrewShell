/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbennani <mbennani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 21:21:23 by mlektaib          #+#    #+#             */
/*   Updated: 2023/05/21 01:22:45 by mbennani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.h"
#include <stdio.h>

int	to_relative_dir(char *dir, char *path)
{
	char	*tmp;

	if (!strncmp(dir, "~/", 2))
	{
		tmp = ft_strjoin(path, dir + 1);
		if (chdir(tmp) == 0)
		{
			free(path);
			free(tmp);
			return (0);
		}
	}
	return (1);
}

int	to_home_dir(t_env **env, char *dir)
{
	char	*path;

	path = NULL;
	path = ft_strjoin("/Users/", getenv("USER"));
	if (get_env(*env, "OLDPWD"))
		exportadd_for_cd(env, envnew("OLDPWD", return_pwd(), 0));
	if (!strcmp(dir, "~"))
	{
		if (chdir(path) == 0)
		{
			free(path);
			return (0);
		}
	}
	else if (!to_relative_dir(dir, path))
		return (0);
	ft_putstr_fd("bash: cd: ", 2);
	ft_putstr_fd(dir, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
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
	ft_putstr_fd("bash: cd: ", 2);
	ft_putstr_fd(path, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
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
	ft_putstr_fd("bash: cd: ", 2);
	ft_putstr_fd(node->u_data.cmd.args[1], 2);
	ft_putstr_fd(": ", 2);
	perror("");
	return (1);
}

int	cd(t_ast *node, t_env **env)
{
	if (!node->u_data.cmd.args[1])
		return (0);
	else
	{
		if (!ft_strncmp(node->u_data.cmd.args[1], "~", 1))
			return (to_home_dir(env, node->u_data.cmd.args[1]));
		else if (!strcmp(node->u_data.cmd.args[1], "-"))
			return (to_prev_dir(env));
		else
			return (to_dir(node, env));
	}
	if (get_env(*env, "PWD"))
		exportadd_for_cd(env, envnew("PWD", return_pwd(), 0));
	return (1);
}
