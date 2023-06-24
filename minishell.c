/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlektaib <mlektaib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 17:47:25 by mbennani          #+#    #+#             */
/*   Updated: 2023/06/24 23:33:59 by mlektaib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <signal.h>

t_global	g_global;

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

int	main(int argc, char *argv[], char *env[])
{
	t_ast	*root;
	char	*input;
	t_env	*envlst;
	int		k;

	(void)argc;
	(void)argv;
	g_global.run = 0;
	signal(SIGINT, signal_hand);
	signal(SIGQUIT, signal_hand);
	root = NULL;
	envlst = load_env(env);
	rl_catch_signals = 0;
	k = 0;
	if(envlst)
	{
		if(get_env(envlst,"SHLVL"))
		{
			char *shlvl = ft_itoa(ft_atoi(get_env(envlst,"SHLVL")->value) + 1);
			add_to_env(&envlst, envnew(ft_strdup("SHLVL"), shlvl, 0));
		}
		else
			envadd_back(&envlst, envnew("SHLVL", "1", 0), 0);
	}
	if (!envlst)
	{
		envadd_back(&envlst, envnew("PATH",
				"/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:.", 0), 1);
		envadd_back(&envlst, envnew("SHLVL", "1", 0), 0);
		envadd_back(&envlst, envnew("PWD", return_pwd(), 0), 0);
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
		if (root)
		{
			execute_all_heredocs(root, &envlst);
			g_global.exit_status = execute_commands(root, &envlst, 0);
			free_ast_node(root);
		}
	}
	return (0);
}
