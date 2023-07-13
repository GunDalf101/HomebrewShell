/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlektaib <mlektaib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 17:47:25 by mbennani          #+#    #+#             */
/*   Updated: 2023/07/13 01:36:41 by mlektaib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <signal.h>

t_global	g_global;

void	initialize_shell(t_env **envlst, int *initial_env)
{
	char	*tmp;

	rl_catch_signals = 0;
	_unsetenv("OLDPWD", envlst);
	_unsetenv("PWD", envlst);
	envadd_back(envlst, envnew("PWD", return_pwd(), 0), 0);
	if (get_env(*envlst, "PATH") == NULL)
	{
		envadd_back(envlst, envnew(ft_strdup("PATH"),
				ft_strdup("/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:."),
				0), 1);
		*initial_env = 1;
	}
	if (get_env(*envlst, "SHLVL") == NULL)
		envadd_back(envlst, envnew(ft_strdup("SHLVL"), ft_strdup("1"), 0), 0);
	else
	{
		tmp = get_env(*envlst, "SHLVL")->value;
		*initial_env = ft_atoi(get_env(*envlst, "SHLVL")->value);
		get_env(*envlst, "SHLVL")->value = ft_itoa(*initial_env + 1);
		free(tmp);
	}
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

	root = parsinginit(input, FALSE);
	execute_input(root, envlst);
}

void	read_execute_loop(t_env **envlst, int initial_env)
{
	char	*input;

	while (1)
	{
		input = NULL;
		g_global.run = 0;
		input = readline("minishell>");
		if (!input)
		{
			if (initial_env == 1)
				ft_putendl_fd("exit", STDOUT_FILENO);
			else
				write(1, "exit\n", 6);
			exit(g_global.exit_status);
		}
		if (input[0] == '\n' || input[0] == '\0')
		{
			free(input);
			continue ;
		}
		add_history(input);
		g_global.run = 1;
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
