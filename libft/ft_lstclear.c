/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbennani <mbennani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 04:49:31 by mbennani          #+#    #+#             */
/*   Updated: 2022/10/20 22:30:12 by mbennani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*temp;

	if (!lst || !*lst || !del)
		return ;
	if (lst && del)
	{
		while (*lst)
		{
			temp = (*lst)->next;
			del((*lst)->content);
			free(*lst);
			*lst = temp;
		}
	}
	*lst = NULL;
}
