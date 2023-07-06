/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlektaib <mlektaib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 21:21:23 by mlektaib          #+#    #+#             */
/*   Updated: 2023/07/06 13:04:33 by mlektaib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.h"

int	to_relative_dir(char *dir, char *path, t_env **env)
{
	char	*tmp;

	if (!strncmp(dir, "~/", 2))
	{
		tmp = ft_strjoin(path, dir + 1);
		if (chdir(tmp) == 0)
		{
			exportadd_for_cd(env, envnew("PWD", return_pwd(), 0));
			free(path);
			free(tmp);
			return (0);
		}
		free(tmp);
	}
	free(path);
	return (1);
}

int	to_home_dir(t_env **env, char *dir)
{
	char	*path;

	path = NULL;
	path = ft_strjoin("/Users/", getenv("USER"));
	exportadd_for_cd(env, envnew("OLDPWD", ft_strdup(get_env(*env, "PWD")->value), 0));
	if (dir == NULL || !ft_strcmp(dir, "~"))
	{
		if (chdir(path) == 0)
		{
			exportadd_for_cd(env, envnew("PWD", return_pwd(), 0));
			free(path);
			return (0);
		}
	}
	else if (!to_relative_dir(dir, path, env))
		return (0);
	ft_putstr_fd("bash: cd: ", 2);
	ft_putendl_fd("Home not set", 2);
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
	exportadd_for_cd(env, envnew("OLDPWD", ft_strdup(get_env(*env, "PWD")->value), 0));
	if (chdir(path) == 0)
	{
		exportadd_for_cd(env, envnew("PWD", return_pwd(), 0));
		path = return_pwd();
		printf("%s\n", path);
		return (free(path), 0);
	}
	ft_putstr_fd("bash: cd: ", 2);
	ft_putstr_fd(path, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
	return (1);
}

int	to_dir(t_ast *node, t_env **env)
{
	char	*path;

	path = NULL;
	if (a_relative_path(node->u_data.cmd.args[1]))
		exportadd_for_cd(env, envnew("PWD", get_tmp_relative(node, env), 0));
	exportadd_for_cd(env, envnew("OLDPWD", ft_strdup(get_env(*env,
				"PWD")->value), 0));
	if (chdir(node->u_data.cmd.args[1]) == 0)
		return (exportadd_for_cd(env, envnew("PWD", return_pwd(), 0)), 0);
	if (a_relative_path(node->u_data.cmd.args[1]))
	{
		ft_putstr_fd("cd: error retrieving current directory: getcwd:", 2);
		ft_putstr_fd("cannot access parent directories", 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return (0);
	}
	ft_putstr_fd("bash: cd: ", 2);
	ft_putstr_fd(node->u_data.cmd.args[1], 2);
	ft_putstr_fd(": No such file or directory\n", 2);
	return (1);
}

int	cd(t_ast *node, t_env **env)
{
	if (!node->u_data.cmd.args[1])
		return (to_home_dir(env, NULL));
	else
	{
		if (!ft_strncmp(node->u_data.cmd.args[1], "~", 1))
			return (to_home_dir(env, node->u_data.cmd.args[1]));
		else if (!ft_strcmp(node->u_data.cmd.args[1], "-"))
			return (to_prev_dir(env));
		else
			return (to_dir(node, env));
	}
	return (1);
}
