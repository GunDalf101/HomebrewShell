/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlektaib <mlektaib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 21:20:24 by mlektaib          #+#    #+#             */
/*   Updated: 2023/04/08 21:20:25 by mlektaib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

int	check_if_dir(char *path)
{
	struct stat	path_stat;

	if (stat(path, &path_stat) == 0)
	{
		if (S_ISDIR(path_stat.st_mode))
		{
			ft_putstr_fd("is dir\n", 2);
			return (126);
		}
	}
	return (0);
}
int	check_if_path(char *cmd)
{
	while (*cmd)
	{
		if (*cmd == '/')
			return (1);
		cmd++;
	}
	return (0);
}
int	find_command_path(t_ast *node, t_env *env)
{
	t_env	*path = get_env(env,"PATH");
	char **paths = ft_split(path->value,':');
	char *cmd;
	char *currtest = NULL;
	cmd = ft_strjoin("/",node->u_data.cmd.cmd);
	int found = 0;

	while(*paths)
	{
		currtest = ft_strjoin(*paths,cmd);

		if (access(currtest, F_OK) == 0 && access(currtest, X_OK) == 0)
		{
			node->u_data.cmd.cmd = currtest;
			return (0);
		}
		paths++;
	}

	return (127);
}
int	check_cmd(t_ast *node, t_env *env)
{
	int k = 0;
	if (get_env(env, "PATH") && check_if_path(node->u_data.cmd.cmd) == 0)
	{
			if (find_command_path(node, env) == 0)
				return (0);
			else
			{
				ft_putstr_fd("bash: command not found",2);
				return 127;
			}
	}
	else
	{
		if (check_if_dir(node->u_data.cmd.cmd))
			return (126);
		else if (access(node->u_data.cmd.cmd, F_OK) != 0)
		{
			ft_putstr_fd("No such file or directory\n", 2);
			return (127);
		}
		else if (access(node->u_data.cmd.cmd, X_OK) != 0)
		{
			ft_putstr_fd("Permission denied\n", 2);
			return (126);
		}
		else if(check_if_path(node->u_data.cmd.cmd) == 0)
			return 1;
		else
			return (0);
	}
	return (0);
}