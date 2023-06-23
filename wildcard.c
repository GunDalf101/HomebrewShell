/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlektaib <mlektaib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 22:56:18 by mbennani          #+#    #+#             */
/*   Updated: 2023/06/23 23:09:45 by mlektaib         ###   ########.fr       */
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

void	wildcard_search(const char *pattern)
{
	char			current_directory[1024];
	DIR				*dir;
	struct dirent	*entry;

	if (getcwd(current_directory, sizeof(current_directory)) == NULL)
	{
		fprintf(stderr, "Error: Failed to get current directory.\n");
		return ;
	}
	dir = opendir(current_directory);
	if (dir == NULL)
	{
		fprintf(stderr, "Error: Failed to open directory.\n");
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
			printf("%s\n", entry->d_name);
	}
	closedir(dir);
}

int	main(void)
{
	const char	*pattern;

	pattern = "*";
	wildcard_search(pattern);
	return (0);
}
