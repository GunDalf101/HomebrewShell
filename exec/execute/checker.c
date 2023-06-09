/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlektaib <mlektaib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 21:20:24 by mlektaib          #+#    #+#             */
/*   Updated: 2023/07/08 15:12:50 by mlektaib         ###   ########.fr       */
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
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(path, 2);
			ft_putstr_fd(": is a directory\n", 2);
			return (126);
		}
	}
	return (0);
}

int	check_if_path(char *cmd)
{
	if (!cmd)
		return (0);
	while (*cmd)
	{
		if (*cmd == '/')
			return (1);
		cmd++;
	}
	return (0);
}

int	checking_current_dir(t_ast *node)
{
	if (check_if_dir(node->u_data.cmd.cmd))
		return (126);
	else if (access(node->u_data.cmd.cmd, F_OK) != 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(node->u_data.cmd.cmd, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return (127);
	}
	else if (access(node->u_data.cmd.cmd, X_OK) != 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(node->u_data.cmd.cmd, 2);
		ft_putstr_fd(": Permission denied\n", 2);
		return (126);
	}
	else if (check_if_path(node->u_data.cmd.cmd) == 0)
		return (1);
	else
		return (0);
}

int	check_cmd(t_ast *node, t_env *env)
{
	if ((get_env(env, "PATH") && check_if_path(node->u_data.cmd.cmd) == 0)
		|| !ft_strlen(node->u_data.cmd.cmd))
	{
		if (find_command_path(node, env) == 0 && ft_strlen(
				node->u_data.cmd.cmd) != 0)
			return (0);
		else
		{
			ft_putstr_fd("minishell: command not found", 2);
			ft_putstr_fd(": ", 2);
			ft_putstr_fd(node->u_data.cmd.cmd, 2);
			ft_putstr_fd("\n", 2);
			return (127);
		}
	}
	else
		return (checking_current_dir(node));
	return (0);
}
