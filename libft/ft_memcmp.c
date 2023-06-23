/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlektaib <mlektaib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 06:24:19 by mbennani          #+#    #+#             */
/*   Updated: 2023/06/23 23:05:10 by mlektaib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp( void *str1, void *str2, size_t n)
{
	size_t					i;
	unsigned char			*s1;
	unsigned char			*s2;

	i = 0;
	s1 = str1;
	s2 = str2;
	if (n == 0)
		return (0);
	while (i < n)
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	i--;
	return (s1[i] - s2[i]);
}
