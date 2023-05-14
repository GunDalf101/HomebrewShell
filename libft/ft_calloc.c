/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbennani <mbennani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 08:59:26 by mbennani          #+#    #+#             */
/*   Updated: 2022/10/23 00:56:12 by mbennani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nitems, size_t size)
{
	void	*v;
	size_t	allo;

	allo = nitems * size;
	if (size != 0 && allo / size != nitems)
		return (NULL);
	v = malloc(allo);
	if (v)
		ft_bzero (v, nitems * size);
	return (v);
}
