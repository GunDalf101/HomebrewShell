/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlektaib <mlektaib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 23:44:29 by mbennani          #+#    #+#             */
/*   Updated: 2023/06/23 23:04:07 by mlektaib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, void *src, size_t n)
{
	unsigned char	*s;
	unsigned char	*d;

	s = src;
	d = dest;
	if (d > s)
	{
		while (n--)
			d[n] = s[n];
	}
	else
		d = ft_memcpy(d, s, n);
	return (d);
}
