/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wild_counter.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbennani <mbennani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 22:03:31 by mbennani          #+#    #+#             */
/*   Updated: 2023/06/24 23:32:16 by mbennani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

int	is_wild(char *str)
{
	int					i;
	int					iswild;
	t_quote_parenthesis	*quotes;

	i = 0;
	iswild = FALSE;
	if (str == NULL)
		return (0);
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
			return (free(quotes), FALSE);
		i++;
	}
	if (iswild == TRUE)
		quotes_remover(str);
	return (free(quotes), iswild);
}

int	is_valid_entry(struct dirent *entry, char *pattern)
{
	if (entry->d_type != DT_REG && entry->d_type != DT_DIR)
	{
		return (0);
	}
	if (entry->d_name[0] == '.' && pattern[0] != '.')
	{
		return (0);
	}
	return (match_pattern(pattern, entry->d_name));
}

int	count_matching_entries(char *pattern)
{
	DIR				*dir;
	int				count;
	struct dirent	*entry;

	dir = opendir(".");
	if (dir == NULL)
	{
		printf("Error: Failed to open directory.\n");
		return (0);
	}
	count = 0;
	entry = readdir(dir);
	while (entry)
	{
		if (is_valid_entry(entry, pattern))
		{
			count++;
		}
		entry = readdir(dir);
	}
	closedir(dir);
	return (count);
}

int	wildcount(char **args, int arg_count)
{
	int	i;
	int	j;

	i = arg_count;
	j = 0;
	while (j < arg_count)
	{
		if (is_wild(args[j]))
		{
			i += count_matching_entries(args[j]);
		}
		j++;
	}
	return (i);
}
