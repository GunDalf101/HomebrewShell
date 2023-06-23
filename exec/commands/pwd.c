/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlektaib <mlektaib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 21:21:37 by mlektaib          #+#    #+#             */
/*   Updated: 2023/06/24 00:48:10 by mlektaib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.h"

char	*return_pwd(void)
{
	char	*buffer;
	size_t	size;
	char	*re_buffer;

	buffer = NULL;
	size = 0;
	re_buffer = NULL;
	while (size <= 4096)
	{
		size += 1024;
		re_buffer = (char *)malloc(size);
		if (re_buffer == NULL)
		{
			free(buffer);
			return (NULL);
		}
		if (getcwd(re_buffer, size) != NULL)
		{
			free(buffer);
			buffer = re_buffer;
			break ;
		}
		free(re_buffer);
	}
	return (buffer);
}

int	pwd(t_env **env)
{
	char	*buffer;

	if (get_env(*env, "PWD"))
	{
		ft_putendl_fd(get_env(*env, "PWD")->value, 1);
		return (0);
	}
	else
	{
		buffer = return_pwd();
		if (buffer == NULL)
			return (1);
		ft_putendl_fd(buffer, 1);
		envnew("PWD", buffer, 0);
	}
	return (0);
}

int	a_relative_path(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	if (str[i] != '.')
		return (0);
	i++;
	while (str[i])
	{
		if (str[i] != '/' && str[i] != '.')
			return (0);
		i++;
	}
	return (1);
}

char	*get_tmp_relative(t_ast *node, t_env **env)
{
	char	*tmp;
	char	*path;

	path = NULL;
	tmp = NULL;
	tmp = ft_strjoin(get_env(*env, "PWD")->value, "/");
	path = ft_strjoin(tmp, node->u_data.cmd.args[1]);
	free(tmp);
	return (path);
}
