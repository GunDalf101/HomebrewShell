/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlektaib <mlektaib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 18:23:45 by mbennani          #+#    #+#             */
/*   Updated: 2023/06/23 23:03:03 by mlektaib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>
#include <stdio.h>

size_t	ft_strlcat(char *dst, char *src, size_t size)
{
	size_t	ls;
	size_t	ld;
	size_t	l;
	size_t	i;
	size_t	j;

	if (size == 0 || size < ft_strlen(dst))
		return (size + ft_strlen(src));
	ld = ft_strlen(dst);
	ls = ft_strlen(src);
	l = ls + ld;
	i = 0;
	j = ld;
	while (src[i] != 0 && j + 1 < size)
	{
		dst[j] = src[i];
		j++;
		i++;
	}
	dst[j] = '\0';
	return (l);
}
