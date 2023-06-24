/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlektaib <mlektaib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 03:16:41 by mlektaib          #+#    #+#             */
/*   Updated: 2023/06/24 19:46:43 by mlektaib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.h"

void	sort_env(char **table, int size)
{
	char	*temp;
	int		i;
	int		j;

	i = 0;
	while (i < size - 1)
	{
		j = 1 + i;
		while (j < size)
		{
			if (strcmp(table[i], table[j]) > 0)
			{
				temp = table[i];
				table[i] = table[j];
				table[j] = temp;
			}
			j++;
		}
		i++;
	}
}

void	free_env(char **env, int size)
{
	int	i;

	(void)size;
	i = 0;
	while (env[i])
	{
		printf("here\n");
		free(env[i]);
		i++;
	}
	free(env);
}
