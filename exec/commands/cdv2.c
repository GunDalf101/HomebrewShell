/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cdv2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlektaib <mlektaib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 06:23:46 by mlektaib          #+#    #+#             */
/*   Updated: 2023/07/15 06:25:00 by mlektaib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.h"

void	fill_stack(t_cd *vars)
{
	int	i;

	i = 0;
	while (vars->tokens[i])
	{
		if (ft_strcmp(vars->tokens[i], ".") != 0 \
			|| ft_strcmp(vars->tokens[i], "..") != 0)
		{
			if (ft_strcmp(vars->tokens[i], "..") == 0)
			{
				if (vars->top >= 0)
					(vars->top)--;
			}
			else if (ft_strcmp(vars->tokens[i], ".") != 0)
				vars->stack[++(vars->top)] = vars->tokens[i];
		}
		i++;
	}
}

void	join_path(t_cd *vars)
{
	int	i;

	i = 0;
	while (i <= vars->top)
	{
		vars->tmp = vars->path;
		vars->path = ft_strjoin(vars->path, "/");
		free(vars->tmp);
		vars->tmp = vars->path;
		vars->path = ft_strjoin(vars->path, vars->stack[i]);
		free(vars->tmp);
		vars->pathlength += strlen(vars->stack[i]) + 1;
		i++;
	}
	i = 0;
	while (vars->tokens[i])
	{
		free(vars->tokens[i]);
		i++;
	}
	free(vars->tokens);
}

void	init_cd_vars(t_cd *vars, char *path)
{
	vars->path = path;
	vars->top = -1;
	vars->pathlength = 0;
	vars->tmp = NULL;
	vars->tokens = NULL;
}

char	*converttoparent(char *path)
{
	t_cd	vars;

	init_cd_vars(&vars, path);
	vars.tokens = ft_split(vars.path, '/');
	fill_stack(&vars);
	vars.pathlength = 0;
	vars.path[0] = '\0';
	join_path(&vars);
	vars.path[vars.pathlength] = '\0';
	if (vars.pathlength == 0)
	{
		free(vars.path);
		vars.path = ft_strdup("/");
	}
	return (vars.path);
}
