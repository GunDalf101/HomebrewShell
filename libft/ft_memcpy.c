/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlektaib <mlektaib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 23:37:38 by mbennani          #+#    #+#             */
/*   Updated: 2023/06/23 23:04:40 by mlektaib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, void *src, size_t n)
{
	size_t				i;
	unsigned char		*s;
	unsigned char		*d;

	i = 0;
	s = src;
	d = dest;
	if (s == 0 && d == 0)
		return (0);
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (d);
}
