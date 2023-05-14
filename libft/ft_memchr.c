/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbennani <mbennani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 06:08:55 by mbennani          #+#    #+#             */
/*   Updated: 2022/10/21 02:12:00 by mbennani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t				i;
	char				ch;
	const char			*str;

	ch = c;
	str = s;
	i = 0;
	while (i < n)
	{
		if (*str == ch)
			return ((void *)str);
		str++;
		i++;
	}
	return (NULL);
}
