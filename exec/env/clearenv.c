/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clearenv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlektaib <mlektaib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 14:42:06 by mlektaib          #+#    #+#             */
/*   Updated: 2023/06/22 15:51:40 by mlektaib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

void	clearenv(t_env **head)
{
	t_env	*tmp;

	while (*head)
	{
		tmp = *head;
		*head = (*head)->next;
		free(tmp->key);
        if (tmp->value)
		    free(tmp->value);
		free(tmp);
	}
	free(*head);
}
