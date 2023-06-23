/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlektaib <mlektaib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 10:46:25 by mbennani          #+#    #+#             */
/*   Updated: 2023/06/23 23:00:50 by mlektaib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	*ft_substr(char *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;
	size_t	size;

	if (ft_strlen(s) < start)
		return (ft_strdup("\0"));
	i = 0;
	size = ft_strlen(s + start);
	if (size < len)
		len = size;
	str = malloc((len + 1) * sizeof(char));
	if (!str || !s)
		return (0);
	while (i < len)
		str[i++] = s[start++];
	str[i] = '\0';
	return (str);
}
