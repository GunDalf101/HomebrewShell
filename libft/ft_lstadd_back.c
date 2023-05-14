/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbennani <mbennani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 14:43:06 by mbennani          #+#    #+#             */
/*   Updated: 2022/10/21 05:22:49 by mbennani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last;

	last = *lst;
	if (*lst == NULL)
		*lst = new;
	else
	{
		while (last->next != NULL)
			last = last->next;
		last->next = new;
	}
}
