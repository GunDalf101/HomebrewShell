/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlektaib <mlektaib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 21:21:32 by mlektaib          #+#    #+#             */
/*   Updated: 2023/04/08 21:21:33 by mlektaib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.h"

int check_key(char *key)
{
	if(!ft_isalpha(key[0]) && key[0] != '_')
		return 0;
	return 1;
}

int envcmd(t_env *head)
{
	while(head)
	{
		ft_putstr_fd(head->key,1);
		ft_putstr_fd("=",1);
		ft_putstr_fd(head->value,1);
		ft_putstr_fd("\n",1);
		head = head->next;
	}
	return 0;
}





