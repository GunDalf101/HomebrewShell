/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wild_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlektaib <mlektaib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 20:44:37 by mbennani          #+#    #+#             */
/*   Updated: 2023/06/24 21:34:18 by mlektaib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

static int	match_pattern(const char *pattern, const char *text)
{
	if (*pattern == '\0' && *text == '\0')
		return (1);
	if (*pattern == '*' && *(pattern + 1) != '\0' && *text == '\0')
		return (0);
	if (*pattern == *text)
		return (match_pattern(pattern + 1, text + 1));
	if (*pattern == '*')
		return (match_pattern(pattern + 1, text) || match_pattern(pattern, text
				+ 1));
	return (0);
}

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
	closedir(dir);
}

int	is_wild(char *str)
{
	int					i;
	int					iswild;
	char				*tmp;
	t_quote_parenthesis	*quotes;

	i = 0;
	iswild = FALSE;
	tmp = ft_strdup(str);
	quotes_remover(tmp);
	quotes = malloc(sizeof(t_quote_parenthesis));
	quotes->dubquo = FALSE;
	quotes->sinquo = FALSE;
	while (str[i])
	{
		super_quote_hander(quotes, str[i]);
		if (str[i] == '*' && quotes->sinquo == FALSE && quotes->dubquo == FALSE)
			iswild = TRUE;
		else if (str[i] == '*' && (quotes->sinquo == TRUE
				|| quotes->dubquo == TRUE))
			return (FALSE);
		i++;
	}
	if (iswild == TRUE)
		quotes_remover(str);
	return (iswild);
}

int	wildcount(char **args, int arg_count)
{
	DIR				*dir;
	struct dirent	*entry;
	int				i;
	int				j;
	int				k;

	i = arg_count;
	j = 0;
	k = 0;
	while (j < arg_count)
	{
		if (is_wild(args[j]))
		{
			dir = opendir(".");
			if (dir == NULL)
			{
				printf("Error: Failed to open directory.\n");
				return (-1);
			}
			entry = readdir(dir);
			while (entry)
			{
				entry = readdir(dir);
				if (entry == NULL)
					break ;
				if (entry->d_type != DT_REG && entry->d_type != DT_DIR)
					continue ;
				if (entry->d_name[0] == '.' && args[j][0] != '.')
					continue ;
				if (match_pattern(args[j], entry->d_name))
					i++;
			}
			closedir(dir);
		}
		j++;
	}
	return (i);
}

void	wildcard_dealer(t_ast *node)
{
	int i;
	int k;
	char **new_args;

	i = 0;
	if (node->type == ast_cmd || node->type == ast_imp)
	{
		i = 0;
		k = 0;
		new_args = malloc(sizeof(char *) * wildcount(node->u_data.cmd.args,
				node->u_data.cmd.arg_count));
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
		node->u_data.cmd.args = new_args;
		node->u_data.cmd.cmd = ft_strdup(node->u_data.cmd.args[0]);
		if (node->u_data.cmd.cmd == NULL)
			node->u_data.cmd.cmd = ft_strdup(node->u_data.cmd.args[0]);
	}
}