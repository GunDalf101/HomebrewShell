/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wild_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbennani <mbennani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 20:44:37 by mbennani          #+#    #+#             */
/*   Updated: 2023/06/24 22:17:03 by mbennani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

void	wildsearch(char *pattern, char **args, int *k)
{
	DIR				*dir;
	struct dirent	*entry;
	int				real;
	int				i;

	real = 0;
	i = *k;
	dir = opendir(".");
	if (dir == NULL)
	{
		printf("Error: Failed to open directory.\n");
		return ;
	}
	entry = readdir(dir);
	while (entry)
	{
		entry = readdir(dir);
		if (entry == NULL)
			break ;
		if (entry->d_type != DT_REG && entry->d_type != DT_DIR)
			continue ;
		if (entry->d_name[0] == '.' && pattern[0] != '.')
			continue ;
		if (match_pattern(pattern, entry->d_name))
		{
			args[*k] = ft_strdup(entry->d_name);
			*k = *k + 1;
			real = 1;
		}
	}
	sort_env(args + i, *k - i);
	if (real == 0)
	{
		args[*k] = ft_strdup(pattern);
		*k = *k + 1;
	}
	free(pattern);
	closedir(dir);
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
		new_args[k] = NULL;
		free(node->u_data.cmd.args);
		node->u_data.cmd.args = new_args;
		free(node->u_data.cmd.cmd);
		node->u_data.cmd.cmd = ft_strdup(node->u_data.cmd.args[0]);
		if (node->u_data.cmd.cmd == NULL)
			node->u_data.cmd.cmd = ft_strdup(node->u_data.cmd.args[0]);
	}
}
