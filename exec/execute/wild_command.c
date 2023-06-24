/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wild_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlektaib <mlektaib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 20:44:37 by mbennani          #+#    #+#             */
/*   Updated: 2023/06/24 23:07:37 by mlektaib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

void	wildreplace(t_wild *wild, char **args, int *real, int *k)
{
	while (wild->entry)
	{
		wild->entry = readdir(wild->dir);
		if (wild->entry == NULL)
			break ;
		if (wild->entry->d_type != DT_REG && wild->entry->d_type != DT_DIR)
			continue ;
		if (wild->entry->d_name[0] == '.' && wild->pattern[0] != '.')
			continue ;
		if (match_pattern(wild->pattern, wild->entry->d_name))
		{
			args[*k] = ft_strdup(wild->entry->d_name);
			*k = *k + 1;
			*real = 1;
		}
	}
}

void	wildsearch(char *pattern, char **args, int *k)
{
	t_wild	wild;
	int		real;

	wild_init(&wild, pattern);
	real = 0;
	wild.i = *k;
	wild.dir = opendir(".");
	if (wild.dir == NULL)
	{
		printf("Error: Failed to open directory.\n");
		return ;
	}
	wild.entry = readdir(wild.dir);
	wildreplace(&wild, args, &real, k);
	sort_env(args + wild.i, *k - wild.i);
	if (real == 0)
	{
		args[*k] = ft_strdup(pattern);
		*k = *k + 1;
	}
	free(pattern);
	closedir(wild.dir);
}

void	finish_him(char **new_args, t_ast *node, int k)
{
	new_args[k] = NULL;
	free(node->u_data.cmd.args);
	node->u_data.cmd.args = new_args;
	free(node->u_data.cmd.cmd);
	node->u_data.cmd.cmd = ft_strdup(node->u_data.cmd.args[0]);
	if (node->u_data.cmd.cmd == NULL)
		node->u_data.cmd.cmd = ft_strdup(node->u_data.cmd.args[0]);
}

void	wildcard_dealer(t_ast *node)
{
	int		i;
	int		k;
	char	**new_args;

	i = 0;
	if (node->type == ast_cmd || node->type == ast_imp)
	{
		i = 0;
		k = 0;
		new_args = ft_calloc(wildcount(node->u_data.cmd.args, \
				node->u_data.cmd.arg_count) + 1, sizeof(char *));
		while (i < node->u_data.cmd.arg_count)
		{
			if (is_wild(node->u_data.cmd.args[i]))
			{
				wildsearch(node->u_data.cmd.args[i], new_args, &k);
				i++;
				continue ;
			}
			new_args[k] = node->u_data.cmd.args[i];
			i++;
			k++;
		}
		finish_him(new_args, node, k);
	}
}
