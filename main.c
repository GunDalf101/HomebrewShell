/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlektaib <mlektaib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 21:20:28 by mlektaib          #+#    #+#             */
/*   Updated: 2023/05/11 18:30:09 by mlektaib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
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

int	main(int argc, char *argv[], char **env)
{
	g_run = 0;
	rl_catch_signals = 0;
	signal(SIGINT, signal_hand);

	// char *randomnum = ft_itoa(generate_rand());
	// char *heredoctmp = ft_strjoin("/tmp/heredoc", randomnum);
	// free(randomnum);
	t_env *envlst = load_env(env);

	while (1)
	{
		char *command2_args[] = {"make","re", NULL};
		t_ast *command2 = add_new_cmd("make", command2_args, 2, ast_cmd);
		g_run = 0;
		input = NULL;
		input = readline("minishell>");
		add_history(input);
		free(input);
		if (!input)
		{
			write(1, "exit\n", 6);
			exit(0);
		}
		g_run = 0;
		g_run = execute_commands(command2, &envlst);
		free_ast_node(command2);
	}
	clearenv(&envlst);
}