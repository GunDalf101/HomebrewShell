/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlektaib <mlektaib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 23:01:32 by mlektaib          #+#    #+#             */
/*   Updated: 2023/06/24 00:24:31 by mlektaib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

static int	isoverflow(long long int prev, long long int curr)
{
	if (curr / 10 == prev)
		return (0);
	return (1);
}

static int	calcul_res(char *str, int i)
{
	long long int	res;
	long long int	prv;

	res = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
		{
			printf("exit\n");
			printf("minishell: exit: %s: numeric argument required\n", str);
			exit(255);
		}
		prv = res;
		res = res * 10 + (str[i] - 48);
		if (isoverflow(prv, res))
		{
			printf("prev == %lld | res  == %lld\n", prv, res);
			printf("exit\n");
			printf("minishell: exit: %s: numeric argument required\n", str);
			exit(255);
		}
		i++;
	}
	return (res);
}

int	exitcmd(t_ast *node, int k)
{
	int				sign;
	long long int	res;
	int				i;

	i = 0;
	sign = 1;
	if (node->u_data.cmd.arg_count > 2 && k == 0)
		printf("exit\nminishell: exit: too many arguments\n");
	if (node->u_data.cmd.arg_count == 2)
	{
		if (node->u_data.cmd.args[1][0] == '-')
		{
			sign = -1;
			i++;
		}
		res = calcul_res(node->u_data.cmd.args[1], i);
		if (k == 0)
			printf("exit\n");
		exit((unsigned char)res);
	}
	if (k == 0)
		printf("exit\n");
	exit(0);
}
