/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbennani <mbennani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 11:57:07 by mbennani          #+#    #+#             */
/*   Updated: 2022/10/21 16:33:47 by mbennani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
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
