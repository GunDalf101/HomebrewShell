/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_with_a_twist.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbennani <mbennani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 14:16:15 by mbennani          #+#    #+#             */
/*   Updated: 2023/06/18 09:56:28 by mbennani         ###   ########.fr       */
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

void	parenthesis_life_time(int *life_counter, char c, int *paren, int sinquo, int dubquo)
{
	if (c == '(' && sinquo == FALSE && dubquo == FALSE)
	{
		*life_counter = *life_counter + 1;
		*paren = TRUE;
	}
	else if (c == ')' && sinquo == FALSE && dubquo == FALSE)
	{
		*life_counter = *life_counter - 1;
	}
	
	if (*life_counter == 0 && *paren == TRUE && sinquo == FALSE && dubquo == FALSE)
		*paren = FALSE;
}

static size_t	ft_countwords(char const *str, char c)
{
	int	i;
	int	count;
	int life_counter;
	int paren;
	int	dubquo;
	int	sinquo;

	if (!str)
		return (0);
	i = 0;
	count = 0;
	dubquo = FALSE;
	sinquo = FALSE;
	paren = FALSE;
	life_counter = 0;
	if (str[i] == '(')
		count++;
	while (str[i])
	{
		super_quote_hander(&dubquo, &sinquo, str[i]);
		parenthesis_life_time(&life_counter, str[i], &paren, sinquo, dubquo);
		if (((sinquo == FALSE && dubquo == FALSE) || str[i - 1] == ' ' ) && (paren == FALSE  || str[i] == ')'))
		{
			while (str[i] == c)
				i++;
			if (str[i] != ')')
				parenthesis_life_time(&life_counter, str[i], &paren, sinquo, dubquo);
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

static size_t	ft_wordlen(char const *str, char c)
{
	size_t	count;
	int	dubquo;
	int	sinquo;
	int paren = FALSE;
	int life_counter = 0;

	count = 0;
	dubquo = FALSE;
	sinquo = FALSE;
	while (str[count] && (str[count] != c || sinquo == TRUE || dubquo == TRUE || life_counter != 0))
	{
		parenthesis_life_time(&life_counter, str[count], &paren, sinquo, dubquo);
		super_quote_hander(&dubquo, &sinquo, str[count]);
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

char	**split_with_a_twist(char const *s, char c)
{
	char **res;
	size_t i;
	unsigned int pos;

	if (!s)
		return (0);
	i = -1;
	pos = 0;
	if (ft_countwords(s, c) == 0)
		return (NULL);
	res = ft_calloc(sizeof(char *), ft_countwords(s, c) + 1);
	if (!res)
		return (0);
	while (++i < ft_countwords(s, c))
	{
		while (s[pos] == c && s[pos])
			pos++;
		res[i] = ft_substr(s, pos, ft_wordlen((s + pos), c));
		if (!(res[i]))
			return (ft_freeall(res, i), NULL);
		pos += ft_wordlen(s + pos, c);
	}
	res[i] = NULL;
	return (res);
}