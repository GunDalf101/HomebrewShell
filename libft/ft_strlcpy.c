/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlektaib <mlektaib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 23:22:36 by mbennani          #+#    #+#             */
/*   Updated: 2023/06/23 23:02:38 by mlektaib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, char *src, size_t size)
{
	size_t	ls;
	size_t	j;

	ls = ft_strlen(src);
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
