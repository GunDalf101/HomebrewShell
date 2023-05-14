/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbennani <mbennani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 21:56:42 by mbennani          #+#    #+#             */
/*   Updated: 2022/10/19 01:06:48 by mbennani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	len_nb(long int n)
{
	long int	len;

	len = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		n = n * -1;
		len++;
	}
	while (n > 0)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

static char	*realitoa(long int n, int i, char *str)
{
	if (n == 0)
	{
		str[0] = 48;
		return (str);
	}
	if (n < 0)
	{
		str[0] = '-';
		n = n * -1;
	}
	while (n > 0)
	{
		str[i] = 48 + (n % 10);
		n = n / 10;
		i--;
	}
	return (str);
}

char	*ft_itoa(int nb)
{
	char		*str;
	int			i;
	long int	n;

	n = nb;
	i = len_nb(n);
	str = (char *)malloc(sizeof(char) * i + 1);
	if (!str)
		return (NULL);
	str[i--] = '\0';
	return (realitoa(n, i, str));
}
