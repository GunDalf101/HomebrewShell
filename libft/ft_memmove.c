/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbennani <mbennani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 23:44:29 by mbennani          #+#    #+#             */
/*   Updated: 2022/10/21 02:57:25 by mbennani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	const unsigned char		*s;
	unsigned char			*d;

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
