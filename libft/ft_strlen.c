/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlektaib <mlektaib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 23:13:28 by mbennani          #+#    #+#             */
/*   Updated: 2023/06/23 23:02:18 by mlektaib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(char *str)
{
	size_t	counter;

	if (!str)
		return (0);
	counter = 0;
	while (str[counter])
		counter++;
	return (counter);
}
