/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbennani <mbennani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 17:47:25 by mbennani          #+#    #+#             */
/*   Updated: 2023/06/20 05:23:28 by mbennani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <signal.h>

t_global g_global;

void	signal_hand(int signum)
{
	if (signum == SIGINT && g_global.run == 0)
	{
		ft_putchar_fd('\n', STDOUT_FILENO);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_global.exit_status = 1;
	}
	if (signum == SIGINT && g_global.run == 1)
	{
		ft_putchar_fd('\n', STDOUT_FILENO);
		rl_on_new_line();
		rl_replace_line("", 0);
		g_global.run = 130;
		g_global.exit_status = 130;
	}
}

int	main(int argc, char *argv[],char *env[])
{
	(void)argc;
	(void)argv;
	g_global.run = 0;
	signal(SIGINT, signal_hand);
	t_ast *root;
	root = NULL;
	char *input;

	rl_catch_signals = 0;

	t_env *envlst = load_env(env);
	int k = 0;
	if (!envlst)
	{
		envadd_back(&envlst, envnew("PATH", "/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:.", 0),1);
		envadd_back(&envlst, envnew("PWD", return_pwd(), 0),0);
		k = 1;
	}
	(void)envlst;
	g_global.run = 0;
	g_global.exit_status = 0;
	while (1)
	{ 
		g_global.run = 0;
		input = NULL;
		root = NULL;
		input = readline("minishell>");
		printf("input = %s\n", input);
		if (!input)
		{
			if (k == 1)
				ft_putendl_fd("\nexit", STDOUT_FILENO);
			else
				write(1, "exit\n", 6);
			break ;
		}
		if (input[0] == '\n' || input[0] == '\0')
		{
			free(input);
			continue ;
		}
		add_history(input);
		root = parsinginit(input);
		printf("gol moussoulini\n");
		if (root)
		{
			// execute_all_heredocs(root, &envlst);
			// g_global.exit_status = execute_commands(root, &envlst);
			free_ast_node(root);
		}
	}
	return (0);
}