/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_with_a_twist.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbennani <mbennani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 14:16:15 by mbennani          #+#    #+#             */
/*   Updated: 2023/07/06 21:01:56 by mbennani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexing_lexer.h"

// this is ft_split but with a twist
//(the whitespace between the quotes is skipped)
int	ft_countwords_extension(char *str, int *count, int *i, \
		t_quote_parenthesis *quotes)
{
	if (!str)
		return (0);
	*i = 0;
	*count = 0;
	quotes->dubquo = FALSE;
	quotes->sinquo = FALSE;
	quotes->paren = FALSE;
	quotes->life_counter = 0;
	if (str[*i] == '(')
		*count = *count + 1;
	return (1);
}

static size_t	ft_countwords(char *str, char c, t_quote_parenthesis *quotes)
{
	int	i;
	int	count;

	if (ft_countwords_extension(str, &count, &i, quotes) == 0)
		return (0);
	while (str[i])
	{
		super_quote_hander(quotes, str[i]);
		parenthesis_life_time(str[i], quotes);
		if ((quotes->sinquo == FALSE && quotes->dubquo == FALSE) && \
		(quotes->paren == FALSE || str[i] == ')'))
		{
			while (str[i] == c)
				i++;
			if (str[i] != ')')
				parenthesis_life_time(str[i], quotes);
			if (str[i] && str[i] != c && str[i] != ')')
				count++;
			while (str[i] != c && str[i])
				i++;
		}
		if (str[i])
			i++;
	}
	return (count);
}

static size_t	ft_wordlen(char *str, char c, t_quote_parenthesis *quotes)
{
	size_t	count;

	count = 0;
	quotes->dubquo = FALSE;
	quotes->sinquo = FALSE;
	quotes->paren = FALSE;
	quotes->life_counter = 0;
	while (str[count] && (str[count] != c || quotes->sinquo == TRUE
			|| quotes->dubquo == TRUE || quotes->life_counter != 0))
	{
		parenthesis_life_time(str[count], quotes);
		super_quote_hander(quotes, str[count]);
		count++;
	}
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

char	**split_with_a_twist(char *s, char c, t_quote_parenthesis *quotes)
{
	char			**res;
	size_t			i;
	unsigned int	pos;

	if (!s)
		return (0);
	i = -1;
	pos = 0;
	if (ft_countwords(s, c, quotes) == 0)
		return (NULL);
	res = ft_calloc(sizeof(char *), ft_countwords(s, c, quotes) + 1);
	if (!res)
		return (0);
	while (++i < ft_countwords(s, c, quotes))
	{
		while (s[pos] == c && s[pos])
			pos++;
		res[i] = ft_substr(s, pos, ft_wordlen((s + pos), c, quotes));
		if (!(res[i]))
			return (ft_freeall(res, i), NULL);
		pos += ft_wordlen(s + pos, c, quotes);
	}
	res[i] = NULL;
	return (res);
}
