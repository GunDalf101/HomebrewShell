/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbennani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 23:22:36 by mbennani          #+#    #+#             */
/*   Updated: 2022/10/08 17:08:48 by mbennani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	ls;
	size_t	l;
	size_t	j;

	ls = ft_strlen(src);
	l = ls;
	if (size == 0)
		return (ls);
	j = 0;
	while (src[j] != 0 && j < size - 1)
	{
		dst[j] = src[j];
		j++;
	}
	dst[j] = '\0';
	return (ls);
}
