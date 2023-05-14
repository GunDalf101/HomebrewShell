/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbennani <mbennani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 04:18:03 by mbennani          #+#    #+#             */
/*   Updated: 2022/10/21 03:34:36 by mbennani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	ch;
	char	*save;

	save = NULL;
	ch = c;
	while (1 != 0)
	{
		if (*s == ch)
			save = ((char *)s);
		if (!*s)
			return (save);
		s++;
	}
	return (NULL);
}
