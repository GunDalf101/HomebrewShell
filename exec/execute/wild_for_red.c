/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wild_for_red.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbennani <mbennani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 20:29:38 by mlektaib          #+#    #+#             */
/*   Updated: 2023/06/24 21:54:44 by mbennani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

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
	DIR				*dir;
	struct dirent	*entry;
	int				i;
	char			*result;
	

	i = 0;

	dir = opendir(".");
	if (dir == NULL)
	{
		fprintf(stderr, "Error: Failed to open directory.\n");
		return (NULL);
	}
	entry = readdir(dir);
	while (entry)
	{
		if (i > 1)
        {
            free(result);
            closedir(dir);
			return (NULL);
        }
		entry = readdir(dir);
		if (entry == NULL)
			break ;
		if (entry->d_type != DT_REG && entry->d_type != DT_DIR)
			continue ;
		if (entry->d_name[0] == '.' && pattern[0] != '.')
			continue ;
		if (match_pattern(pattern, entry->d_name))
		{   if(i == 1)
                free(result);
			result = ft_strdup(entry->d_name);
			i++;
		}
	}
	closedir(dir);
    if (i == 0)
        return (pattern);
	return (result);
}
