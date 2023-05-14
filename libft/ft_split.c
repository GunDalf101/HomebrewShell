/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbennani <mbennani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 01:02:56 by mbennani          #+#    #+#             */
/*   Updated: 2022/10/23 20:17:29 by mbennani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	wordcounter(const char *str, char c)
{
	size_t	i;
	size_t	num;

	i = 0;
	num = 0;
	while (*str)
	{
		if (*str != c && num == 0)
		{
			num = 1;
			i++;
		}
		else if (*str == c)
			num = 0;
		str++;
	}
	return (i);
}

static char	*wordput(const char *str, size_t start, size_t finish)
{
	char		*word;
	size_t		i;

	i = 0;
	word = malloc((finish - start + 1) * sizeof(char));
	if (!word)
		return (NULL);
	while (start < finish)
		word[i++] = str[start++];
	word[i] = '\0';
	return (word);
}

static char	**free_all(char **s, size_t i)
{
	while (i >= 0 && s[i] != NULL)
	{
		free(s[i]);
		s[i] = NULL;
		i--;
	}
	free(s);
	s = NULL;
	return (NULL);
}

static void	valinit(size_t *i, size_t *j, int *id)
{
	*i = -1;
	*j = 0;
	*id = -1;
}

char	**ft_split(char const *s, char c)
{
	size_t	i;
	size_t	j;
	int		id;
	char	**doublestr;

	valinit (&i, &j, &id);
	if (!s)
		return (0);
	doublestr = malloc((wordcounter(s, c) + 1) * sizeof(char *));
	if (!doublestr)
		return (NULL);
	while (++i <= ft_strlen(s))
	{
		if (s[i] != c && id < 0)
			id = i;
		else if ((s[i] == c || i == ft_strlen(s)) && id >= 0)
		{
			doublestr[j] = wordput(s, id, i);
			if (!doublestr[j++] && i < wordcounter(s, c))
				return (free_all(doublestr, --j));
			id = -1;
		}
	}
	doublestr[j] = 0;
	return (doublestr);
}
