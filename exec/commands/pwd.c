/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlektaib <mlektaib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 21:21:37 by mlektaib          #+#    #+#             */
/*   Updated: 2023/07/15 06:09:25 by mlektaib         ###   ########.fr       */
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

	buffer = NULL;
	buffer = return_pwd();
	if (buffer && ft_strlen(buffer) < 4096)
	{
		exportadd_for_cd(env, envnew(ft_strdup("MY_$PWD"),
				ft_strdup(buffer), 0));
		ft_putendl_fd(buffer, 1);
		free(buffer);
		return (0);
	}
	else if (get_env(*env, "MY_$PWD"))
	{
		ft_putendl_fd(get_env(*env, "MY_$PWD")->value, 1);
		return (0);
	}
	ft_putendl_fd(RLTVERROR, 2);
	free(buffer);
	return (1);
}

int	a_relative_path(char *str)
{
	int		i;
	char	**splited;
	int		r;

	splited = ft_split(str, '/');
	i = 0;
	r = 1;
	while (splited[i])
	{
		if (ft_strcmp(splited[i], "..") && ft_strcmp(splited[i], "."))
		{	
			r = 0;
			break ;
		}
		i++;
	}
	i = 0;
	while (splited[i])
	{
		free(splited[i]);
		i++;
	}
	free(splited);
	return (r);
}

char	*get_tmp_relative(t_ast *node, t_env **env)
{
	char	*tmp;
	char	*path;

	path = NULL;
	tmp = NULL;
	tmp = ft_strjoin(get_env(*env, "MY_$PWD")->value, "/");
	path = ft_strjoin(tmp, node->u_data.cmd.args[1]);
	free(tmp);
	return (path);
}
