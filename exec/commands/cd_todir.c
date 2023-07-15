/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_todir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlektaib <mlektaib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 06:29:53 by mlektaib          #+#    #+#             */
/*   Updated: 2023/07/15 07:54:54 by mlektaib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.h"

int	chechpath(char	*path)
{
	struct stat	st;

	if (stat(path, &st) == 0)
		return (1);
	else
		return (0);
}

int	check_permission(char *path)
{
	if (access(path, F_OK) == 0 && access(path, X_OK) == -1)
		return (1);
	if (access(path, F_OK) == -1 && access(path, X_OK) == -1)
		return (2);
	return (0);
}

char	*to_dir_relative(char *path, t_ast *node, t_env **env)
{
	free(path);
	path = get_tmp_relative(node, env);
	exportadd_for_cd(env, envnew(ft_strdup("MY_$PWD"), \
	get_tmp_relative(node, env), 0));
	exportadd_for_cd(env, envnew(ft_strdup("PWD"), \
	get_tmp_relative(node, env), 0));
	return (converttoparent(path));
}

int	permission_denied(char *path, t_ast *node, t_env **env, char *oldpwd)
{
	if (check_permission(path) == 2 && \
			a_relative_path(node->u_data.cmd.args[1]))
	{
		ft_putendl_fd(RLTVERROR, 2);
		chdir(path);
		free(path);
		free(oldpwd);
		return (1);
	}
	exportadd_for_cd(env, envnew(ft_strdup("MY_$PWD"), ft_strdup(oldpwd), 0));
	exportadd_for_cd(env, envnew(ft_strdup("PWD"), ft_strdup(oldpwd), 0));
	chdir(oldpwd);
	perror("minishell: cd");
	free(path);
	return (free(oldpwd), 1);
}

int	to_dir(t_ast *node, t_env **env)
{
	char	*path;
	char	*oldpwd;

	oldpwd = ft_strdup(get_env(*env, "MY_$PWD")->value);
	path = NULL;
	path = ft_strdup(node->u_data.cmd.args[1]);
	exportadd_for_cd(env, envnew(ft_strdup("OLDPWD"), ft_strdup(get_env(*env,
					"PWD")->value), 0));
	if (a_relative_path(node->u_data.cmd.args[1]))
		path = to_dir_relative(path, node, env);
	if (check_permission(path))
		return (permission_denied(path, node, env, oldpwd));
	if (chdir(path) != -1)
		return (free(oldpwd), free(path), \
			exportadd_for_cd(env, envnew(ft_strdup("PWD"), \
			return_pwd(), 0)), exportadd_for_cd(env, envnew(\
				ft_strdup("MY_$PWD"), return_pwd(), 0)), 0);
	if (a_relative_path(node->u_data.cmd.args[1]) && !chechpath(path) \
			&& errno == ENOENT)
		return (free(oldpwd), ft_putendl_fd(RLTVERROR, 2), free(path), 1);
	return (free(oldpwd), free(path), perror("minishell: cd"), 1);
}
