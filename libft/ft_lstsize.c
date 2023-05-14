/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbennani <mbennani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 13:22:52 by mbennani          #+#    #+#             */
/*   Updated: 2022/10/14 13:54:18 by mbennani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int		counter;
	t_list	*curr;

	counter = 0;
	curr = lst;
	while (curr != NULL)
	{
		counter++;
		curr = curr->next;
	}
	return (counter);
}
