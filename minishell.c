/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbennani <mbennani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 17:47:25 by mbennani          #+#    #+#             */
/*   Updated: 2023/06/24 23:47:19 by mbennani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <signal.h>

t_global	g_global;

void	initialize_shell(t_env **envlst, int *initial_env)
{
	rl_catch_signals = 0;
	if (!*envlst)
	{
		envadd_back(envlst, envnew("PATH",
				"/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:.", 0), 1);
		envadd_back(envlst, envnew("PWD", return_pwd(), 0), 0);
		*initial_env = 1;
	}
	g_global.run = 0;
	g_global.exit_status = 0;
}

void	execute_input(t_ast *root, t_env **envlst)
{
	if (root)
	{
		execute_all_heredocs(root, envlst);
		g_global.exit_status = execute_commands(root, envlst, 0);
		free_ast_node(root);
	}
}

void	execute_command(t_env **envlst, char *input)
{
	t_ast	*root;

	root = parsinginit(input);
	execute_input(root, envlst);
}

void	read_execute_loop(t_env **envlst, int initial_env)
{
	char	*input;

	while (1)
	{
		input = NULL;
		input = readline("minishell>");
		if (!input)
		{
			if (initial_env == 1)
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
		execute_command(envlst, input);
	}
}

int	main(int argc, char *argv[], char *env[])
{
	t_env	*envlst;
	int		initial_env;

	initial_env = 0;
	(void)argc;
	(void)argv;
	envlst = load_env(env);
	signal(SIGINT, signal_hand);
	signal(SIGQUIT, signal_hand);
	initialize_shell(&envlst, &initial_env);
	read_execute_loop(&envlst, initial_env);
	return (0);
}
