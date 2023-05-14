/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbennani <mbennani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 16:33:09 by mbennani          #+#    #+#             */
/*   Updated: 2022/10/21 05:11:15 by mbennani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	isset(char c, const char *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static int	ftrimlen(int len, const char *s, const char *set)
{
	int	i;
	int	j;

	i = 0;
	j = len - 1;
	while (s[i] && isset(s[i], set) == 1 && len > 1)
	{
		i++;
		len--;
	}
	while (s[j] && isset(s[j], set) == 1 && len > 1)
	{
		j--;
		len--;
	}
	return (len);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		j;
	int		len;
	int		trimlen;
	char	*news;

	if (!s1)
		return (0);
	i = 0;
	j = 0;
	len = ft_strlen(s1);
	trimlen = ftrimlen(len, s1, set);
	news = malloc((trimlen + 1) * sizeof(char));
	if (!news)
		return (0);
	while (s1[i] && isset(s1[i], set) == 1)
		i++;
	while (j < trimlen)
	{
		news[j] = s1[i];
		i++;
		j++;
	}
	news[j] = '\0';
	return (news);
}
