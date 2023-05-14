/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbennani <mbennani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 08:52:23 by mbennani          #+#    #+#             */
/*   Updated: 2022/10/23 02:06:50 by mbennani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	isoverflow(long long int prev, long long int curr)
{
	if (curr / 10 == prev)
		return (0);
	return (1);
}

static int	itisspace(const char *str, int *pi)
{
	int	count;
	int	i;

	i = 0;
	count = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == 45)
	{
		count = -1;
		i++;
	}
	else if (str[i] == 43)
		i++;
	*pi = i;
	return (count);
}

int	ft_atoi(const char *str)
{
	int				sign;
	long long int	res;
	long long int	prv;
	int				i;

	res = 0;
	sign = itisspace(str, &i);
	while (str[i] && str[i] >= 48 && str[i] <= 57)
	{
		prv = res;
		res = res * 10 + (str[i] - 48);
		if (isoverflow(prv, res) == 1)
		{
			if (sign == -1)
				return (0);
			return (-1);
		}
		i++;
	}
	res *= sign;
	return (res);
}
