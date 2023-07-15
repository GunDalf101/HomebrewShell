/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlektaib <mlektaib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 21:21:23 by mlektaib          #+#    #+#             */
/*   Updated: 2023/07/15 10:46:25 by mlektaib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.h"

int	to_relative_dir(char *dir, char *path, t_env **env)
{
	char	*tmp;

	if (!strncmp(dir, "~/", 2))
	{
		tmp = ft_strjoin(path, dir + 1);
		if (chdir(tmp) != -1)
		{
			exportadd_for_cd(env, envnew(ft_strdup("PWD"), return_pwd(), 0));
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
	exportadd_for_cd(env, envnew(ft_strdup("OLDPWD"),
			ft_strdup(get_env(*env, "PWD")->value), 0));
	if (get_env(*env, "HOME"))
		path = ft_strdup(get_env(*env, "HOME")->value);
	if (!ft_strcmp(dir, "~") && path)
	{
		if (chdir(path) != -1)
		{
			exportadd_for_cd(env, envnew(ft_strdup("PWD"), return_pwd(), 0));
			exportadd_for_cd(env, envnew(ft_strdup("MY_$PWD"), \
				return_pwd(), 0));
			free(path);
			return (0);
		}
	}
	else if (!to_relative_dir(dir, path, env))
		return (0);
	ft_putstr_fd("minishell: cd: ", 2);
	ft_putendl_fd("HOME not set", 2);
	free(path);
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
		ft_putendl_fd("minishell: cd: OLDPWD not set", 2);
		return (1);
	}
	exportadd_for_cd(env, envnew(ft_strdup("OLDPWD"),
			ft_strdup(get_env(*env, "PWD")->value), 0));
	if (chdir(path) != -1)
	{
		exportadd_for_cd(env, envnew(ft_strdup("PWD"), return_pwd(), 0));
		exportadd_for_cd(env, envnew(ft_strdup("MY_$PWD"), return_pwd(), 0));
		path = return_pwd();
		return (free(path), 0);
	}
	perror("minishell: cd");
	return (1);
}

int	cd(t_ast *node, t_env **env)
{
	if (!node->u_data.cmd.args[1])
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putendl_fd("No arguments were given", 2);
		return (1);
	}
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
