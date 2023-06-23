/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlektaib <mlektaib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 11:57:07 by mbennani          #+#    #+#             */
/*   Updated: 2023/06/23 23:03:07 by mlektaib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char *s1, char *s2)
{
	char		*str;
	size_t		l1;
	size_t		l2;

	if (!s1 || !s2)
		return (NULL);
	l1 = ft_strlen(s1);
	l2 = ft_strlen(s2);
	str = malloc((l1 + l2 + 1) * sizeof(char));
	if (!str)
		return (0);
	str = ft_memmove(str, s1, l1 + 1);
	str = str + l1;
	str = ft_memmove(str, s2, l2 + 1);
	str = str - l1;
	return (str);
}
