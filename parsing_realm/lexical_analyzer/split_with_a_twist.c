/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_with_a_twist.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbennani <mbennani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 14:16:15 by mbennani          #+#    #+#             */
/*   Updated: 2023/05/23 15:10:20 by mbennani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexing_lexer.h"

//this is ft_split but with a twist (the whitespace between the quotes is skipped)

void	super_quote_hander(int *dubquo, int *sinquo, char c)
{
	if (c == '\'' && *sinquo == FALSE && *dubquo == FALSE)
		*sinquo = TRUE;
	else if (c == '\'' && *sinquo == TRUE && *dubquo == FALSE)
		*sinquo = FALSE;
	if (c == '"' && *dubquo == FALSE && *sinquo == FALSE)
		*dubquo = TRUE;
	else if (c == '"' && *dubquo == TRUE && *sinquo == FALSE)
		*dubquo = FALSE;
}

static size_t	ft_countwords(char const *str, char c)
{
	int	i;
	int	count;
	int	dubquo;
	int	sinquo;

	if (!str)
		return (0);
	i = 0;
	count = 0;
	dubquo = FALSE;
	sinquo = FALSE;
	while (str[i])
	{
		super_quote_hander(&dubquo, &sinquo, str[i]);
		if (sinquo == FALSE && dubquo == FALSE)
		{
			while (str[i] == c)
					i++;
			if (str[i] != c && str[i])
				count++;
			while (str[i] != c && str[i])
				i++;
		}
		i++;
	}
	return (count);
}

static size_t	ft_wordlen(char const *str, char c)
{
	size_t	count;
	int	dubquo;
	int	sinquo;

	count = 0;
	dubquo = FALSE;
	sinquo = FALSE;
	while (str[count] && (str[count] != c || sinquo == TRUE || dubquo == TRUE))
	{
		super_quote_hander(&dubquo, &sinquo, str[count]);
		count++;
	}
	if (dubquo == TRUE || sinquo == TRUE)
		return (printf("The fuck you doing mate\n"), exit(1), 0);
	return (count);
}

static void	ft_freeall(char **ptr, size_t i)
{
	size_t	j;

	j = 0;
	while (j <= i)
	{
		free(ptr[j]);
		j++;
	}
	free(ptr);
}

char	**split_with_a_twist(char const *s, char c)
{
	char **res;
	size_t i;
	unsigned int pos;

	if (!s)
		return (0);
	i = -1;
	pos = 0;
	res = malloc(sizeof(char *) * ft_countwords(s, c) + 1);
	if (!res)
		return (0);
	while (++i < ft_countwords(s, c))
	{
		while (s[pos] == c && s[pos])
			pos++;
		res[i] = ft_substr(s, pos, ft_wordlen((s + pos), c));
		if (!(res[i]))
		{
			ft_freeall(res, i);
			return (0);
		}
		pos += ft_wordlen(s + pos, c);
	}
	res[i] = NULL;
	return (res);
}