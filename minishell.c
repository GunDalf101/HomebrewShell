/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlektaib <mlektaib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 17:47:25 by mbennani          #+#    #+#             */
/*   Updated: 2023/06/08 15:31:48 by mlektaib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <signal.h>

int		g_run;
char	*input;

void	signal_hand(int signum)
{
	if (signum == SIGINT)
	{
		ft_putchar_fd('\n', STDOUT_FILENO);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_run = 130;
	}
}

int	main(int argc, char *argv[],char *env[])
{
	(void)argc;
	(void)argv;
	g_run = 0;
	signal(SIGINT, signal_hand);
	t_ast *root;
	root = NULL;

	rl_catch_signals = 0;

	t_env *envlst = load_env(env);
	(void)envlst;
	while (1)
	{
		

		g_run = 0;
		input = NULL;
		root = NULL;
		input = readline("minishell>");
		if (!input)
		{
			write(1, "exit\n", 6);
			break ;
		}
		if (input[0] == '\n' || input[0] == '\0')
			continue ;
		add_history(input);
		root = parsinginit(input);
		if (root)
			g_run = execute_commands(root, &envlst);
	
	}
	// clearenv(&envlst);
	return (0);
}