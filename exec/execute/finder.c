/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finder.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlektaib <mlektaib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 18:41:17 by mlektaib          #+#    #+#             */
/*   Updated: 2023/07/08 18:06:20 by mlektaib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

extern t_global	g_global;

void	exec_cmd(t_ast *node, t_env **env)
{
	execve(node->u_data.cmd.cmd, node->u_data.cmd.args, lst_to_env(*env));
	perror(node->u_data.cmd.cmd);
	exit(1);
}

void	free_paths(char **paths)
{
	int	i;

	i = 0;
	while (paths[i])
		free(paths[i++]);
	free(paths);
}

int	test_cmd(char *cmd, char *path, t_ast *node, char **paths)
{
	char	*currtest;
	char	*tmp;

	currtest = ft_strjoin(path, cmd);
	if (access(currtest, F_OK) == 0 && access(currtest, X_OK) == 0)
	{
		tmp = node->u_data.cmd.cmd;
		node->u_data.cmd.cmd = currtest;
		free(cmd);
		free(tmp);
		free_paths(paths);
		return (1);
	}
	free(currtest);
	return (0);
}

int	find_command_path(t_ast *node, t_env *env)
{
	t_env	*path;
	char	**paths;
	char	*cmd;
	int		i;

	i = 0;
	if (ft_strlen(node->u_data.cmd.cmd) == 0)
		return (0);
	path = get_env(env, "PATH");
	paths = ft_split(path->value, ':');
	cmd = ft_strjoin("/", node->u_data.cmd.cmd);
	while (paths[i])
	{
		if (test_cmd(cmd, paths[i], node, paths))
			return (0);
		i++;
	}
	free_paths(paths);
	free(cmd);
	return (127);
}
