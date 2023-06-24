/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbennani <mbennani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 22:56:18 by mbennani          #+#    #+#             */
/*   Updated: 2023/06/24 20:30:39 by mbennani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int	match_pattern(const char *pattern, const char *text)
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

char	*wild_redirection(char *pattern)
{
	char			current_directory[1024];
	DIR				*dir;
	struct dirent	*entry;
	int				i;
	char			*result;
	

	i = 0;
	if (getcwd(current_directory, sizeof(current_directory)) == NULL)
	{
		fprintf(stderr, "Error: Failed to get current directory.\n");
		return (NULL);
	}
	dir = opendir(current_directory);
	if (dir == NULL)
	{
		fprintf(stderr, "Error: Failed to open directory.\n");
		return (NULL);
	}
	entry = readdir(dir);
	while (entry)
	{
		if (i > 0)
			return (NULL);
		entry = readdir(dir);
		if (entry == NULL)
			break ;
		if (entry->d_type != DT_REG && entry->d_type != DT_DIR)
			continue ;
		if (entry->d_name[0] == '.' && pattern[0] != '.')
			continue ;
		if (match_pattern(pattern, entry->d_name))
		{
			result = ft_strdup(entry->d_name);
			i++;
		}
	}
	closedir(dir);
	free(pattern);
	return (result);
}

int	main(void)
{
	const char	*pattern;

	pattern = "*";
	wildcard_search(pattern);
	return (0);
}
