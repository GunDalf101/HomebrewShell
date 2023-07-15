/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_todir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlektaib <mlektaib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 06:29:53 by mlektaib          #+#    #+#             */
/*   Updated: 2023/07/15 06:32:19 by mlektaib         ###   ########.fr       */
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

int	check_permission_for_cd(char *path)
{
	if (access(path, F_OK) && !access(path, X_OK))
		return (1);
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

int	to_dir(t_ast *node, t_env **env)
{
	char	*path;

	path = NULL;
	path = ft_strdup(node->u_data.cmd.args[1]);
	exportadd_for_cd(env, envnew(ft_strdup("OLDPWD"), ft_strdup(get_env(*env,
					"PWD")->value), 0));
	if (a_relative_path(node->u_data.cmd.args[1]))
		path = to_dir_relative(path, node, env);
	if (check_permission_for_cd(path))
	{
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd(node->u_data.cmd.args[1], 2);
		ft_putstr_fd(": Permission denied\n", 2);
		free(path);
		return (1);
	}
	if (chdir(path) != -1)
		return (free(path), exportadd_for_cd(env, envnew(ft_strdup("PWD"), \
			return_pwd(), 0)), exportadd_for_cd(env, envnew(\
				ft_strdup("MY_$PWD"), return_pwd(), 0)), 0);
	if (a_relative_path(node->u_data.cmd.args[1]) && !chechpath(path) \
			&& errno == ENOENT)
		return (ft_putendl_fd(RLTVERROR, 2), free(path), 1);
	return (free(path), perror("minishell: cd"), 1);
}
