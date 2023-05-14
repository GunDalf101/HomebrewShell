/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbennani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 19:39:28 by mbennani          #+#    #+#             */
/*   Updated: 2022/10/07 19:50:52 by mbennani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	char	c;

	if (n == -2147483648)
		write(fd, "-2147483648", 11);
	else if (n >= 0 && n <= 9)
	{
		c = n + 48;
		write (fd, &c, 1);
	}
	else if (n < 0)
	{
		write (fd, "-", 1);
		ft_putnbr_fd (-n, fd);
	}
	else if (n > 0)
	{
		ft_putnbr_fd (n / 10, fd);
		ft_putnbr_fd (n % 10, fd);
	}
}
