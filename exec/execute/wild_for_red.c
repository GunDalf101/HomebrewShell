/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wild_for_red.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbennani <mbennani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 20:29:38 by mlektaib          #+#    #+#             */
/*   Updated: 2023/06/24 23:37:43 by mbennani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

int	match_pattern(char *pattern, char *text)
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

void	wild_init(t_wild *wild, char *pattern)
{
	wild->i = 0;
	wild->result = NULL;
	wild->pattern = pattern;
	wild->dir = NULL;
	wild->entry = NULL;
}

char	*wild_helper(t_wild *wild)
{
	while (wild->entry)
	{
		if (wild->i > 1)
		{
			free(wild->result);
			free(wild->pattern);
			closedir(wild->dir);
			return (NULL);
		}
		wild->entry = readdir(wild->dir);
		if (wild->entry == NULL)
			break ;
		if (wild->entry->d_type != DT_REG && wild->entry->d_type != DT_DIR)
			continue ;
		if (wild->entry->d_name[0] == '.' && wild->pattern[0] != '.')
			continue ;
		if (match_pattern(wild->pattern, wild->entry->d_name))
		{
			if (wild->i == 1)
				free(wild->result);
			wild->result = ft_strdup(wild->entry->d_name);
			wild->i++;
		}
	}
	return (wild->result);
}

char	*wild_redirection(char *pattern)
{
	t_wild		wild;

	wild_init(&wild, pattern);
	wild.dir = opendir(".");
	if (wild.dir == NULL)
	{
		fprintf(stderr, "Error: Failed to open directory.\n");
		return (NULL);
	}
	wild.entry = readdir(wild.dir);
	wild.result = wild_helper(&wild);
	if (wild.result == NULL)
		return (NULL);
	closedir(wild.dir);
	if (wild.i == 0)
		return (pattern);
	free(wild.pattern);
	return (wild.result);
}
