/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlektaib <mlektaib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 06:08:55 by mbennani          #+#    #+#             */
/*   Updated: 2023/06/23 23:05:23 by mlektaib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(void *s, int c, size_t n)
{
	size_t			i;
	char			ch;
	char			*str;

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
