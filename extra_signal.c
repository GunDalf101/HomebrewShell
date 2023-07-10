/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra_signal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlektaib <mlektaib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 23:46:55 by mbennani          #+#    #+#             */
/*   Updated: 2023/07/10 09:00:37 by mlektaib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <signal.h>

extern t_global	g_global;

void	signal_hand(int signum)
{
	if (signum == SIGQUIT)
	{
		if (waitpid(-1, NULL, WNOHANG) == 0)
			return ;
	}
	if (signum == SIGINT && g_global.run == 0)
	{
		ft_putchar_fd('\n', STDOUT_FILENO);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_global.exit_status = 1;
	}
	if (signum == SIGINT && g_global.run > 0)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		g_global.run = 130;
		g_global.exit_status = 130;
	}
}
