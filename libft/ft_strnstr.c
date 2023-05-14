/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbennani <mbennani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 08:43:24 by mbennani          #+#    #+#             */
/*   Updated: 2022/10/19 01:12:56 by mbennani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *to_find, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (to_find[j] == '\0')
		return ((char *)str);
	while (i < len && str[i])
	{
		while (str[i + j] == to_find[j] && str[i + j] != '\0' && (i + j) < len)
			j++;
		if (to_find[j] == '\0')
			return ((char *)str + i);
		i++;
		j = 0;
	}
	return (0);
}
