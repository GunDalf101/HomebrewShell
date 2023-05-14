/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbennani <mbennani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 17:47:25 by mbennani          #+#    #+#             */
/*   Updated: 2023/05/14 21:54:30 by mbennani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/readline.h>
#include <readline/history.h>
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
	(void)argc;
	(void)argv;
	g_run = 0;
	rl_catch_signals = 0;
	signal(SIGINT, signal_hand);
	t_ast *root;

	// char *randomnum = ft_itoa(generate_rand());
	// char *heredoctmp = ft_strjoin("/tmp/heredoc", randomnum);
	// free(randomnum);
	t_env *envlst = load_env(env);

	while (1)
	{
		
		g_run = 0;
		input = NULL;
		input = readline("minishell>");
		add_history(input);
		root = parsing(input);
		free(input);
		if (!input)
		{
			write(1, "exit\n", 6);
			exit(0);
		}
		g_run = 0;
		g_run = execute_commands(root, &envlst);
		free_ast_node(root);
	}
	clearenv(&envlst);
}