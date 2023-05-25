/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbennani <mbennani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 17:47:25 by mbennani          #+#    #+#             */
/*   Updated: 2023/05/19 15:18:06 by mbennani         ###   ########.fr       */
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

int	main(int argc, char *argv[])
{
	(void)argc;
	(void)argv;
	g_run = 0;
	signal(SIGINT, signal_hand);
	t_ast *root;
	root = NULL;

	rl_catch_signals = 0;

	// t_env *envlst = load_env(env);
	while (1)
	{
		

		g_run = 0;
		input = NULL;
		input = readline("minishell>");
		add_history(input);
		if (!input)
		{
			write(1, "exit\n", 6);
			break ;
		}
		root = parsinginit(input);
		free(input);
		free(root);
		// char *heredoctmp = ft_strdup("/tmp/heredoc");

		// // char *command2_args[] = {"wc", "-l", NULL};
		// // t_ast *command2 = add_new_cmd("wc", command2_args, 2, ast_cmd);

		// t_ast *heredoc1 = malloc(sizeof(t_ast));
		// heredoc1->type = ast_heredoc;
		// heredoc1->u_data.heredoc.cmd = NULL;
		// heredoc1->u_data.heredoc.delim = ft_strdup("dd");
		// heredoc1->u_data.heredoc.tmp = heredoctmp;


		// heredoc1->u_data.heredoc.next = NULL;
		// // out->u_data.redirect_out.next = NULL;
		// // out2->u_data.redirect_out.next = NULL;
		// root = heredoc1;
		// g_run = 0;
		// g_run = execute_commands(heredoc1, &envlst);
		// free_ast_node(heredoc1);
		// unlink(heredoctmp);
	}
	// clearenv(&envlst);
	return (0);
}