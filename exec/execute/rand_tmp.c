/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rand_tmp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbennani <mbennani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 21:20:53 by mlektaib          #+#    #+#             */
/*   Updated: 2023/06/22 21:15:43 by mbennani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <sys/stat.h>

int	get_time(void)
{
	struct stat	file_stat;

	if (stat("./minishell", &file_stat) != 0)
	{
		perror("bash : stat");
		return (1);
	}
	return (file_stat.st_atime);
}

int	generate_rand(void)
{
	int					a;
	int					c;
	int					m;
	static unsigned int	ref;
	unsigned int		x;

	a = 1103515245;
	c = 12345;
	m = 214748368;
	ref += (unsigned int)get_time();
	ref = (a * ref + c) % m;
	x = ref;
	return (x);
}
