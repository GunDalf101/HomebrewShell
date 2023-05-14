/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbennani <mbennani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 23:19:11 by mbennani          #+#    #+#             */
/*   Updated: 2022/10/21 05:13:33 by mbennani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *str, int c, size_t n)
{
	size_t				i;
	unsigned char		*s;

	i = 0;
	s = str;
	while (i < n)
	{
		s[i] = c;
		i++;
	}
	return (s);
}
