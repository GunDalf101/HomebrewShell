/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbennani <mbennani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 00:00:51 by mbennani          #+#    #+#             */
/*   Updated: 2022/10/21 03:23:12 by mbennani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	ch;

	ch = c;
	while (s || !s)
	{
		if (*s == ch)
			return ((char *)s);
		if (*s == '\0')
			return (NULL);
		s++;
	}
	return (NULL);
}
