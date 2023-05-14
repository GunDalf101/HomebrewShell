/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlektaib <mlektaib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 21:20:28 by mlektaib          #+#    #+#             */
/*   Updated: 2023/05/01 14:32:08 by mlektaib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <signal.h>

int		run;
char	*input;
void	handler(int sig)
{
	if (run == 0  || run == 130)
	{
		write(STDOUT_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else
		write(STDOUT_FILENO, "\n", 1);
}

int	main(int argc, char *argv[], char **env)
{
	run = 0;
	rl_catch_signals = 0;

	char *heredoctmp = ft_strjoin("/tmp/heredoc", ft_itoa(generate_rand()));
	t_env *envlst = load_env(env);
	t_env *tmp;

	char *command2_args[] = {"wc", "-l", NULL};
	t_ast *command2 = add_new_cmd("wc", command2_args, 2, ast_cmd);

	t_ast *heredoc1 = malloc(sizeof(t_ast));
	heredoc1->type = ast_heredoc;
	heredoc1->u_data.heredoc.cmd = command2;
	heredoc1->u_data.heredoc.delim = "dd";
	heredoc1->u_data.heredoc.tmp = heredoctmp;

	//wc -l << dd > test2 > test 3 < input
	t_ast *in = malloc(sizeof(t_ast));
	in->type = ast_redirect_in;
	in->u_data.redirect_in.cmd = NULL;
	in->u_data.redirect_in.next = NULL;
	in->u_data.redirect_in.infile = "input";

	t_ast *out = malloc(sizeof(t_ast));
	out->type = ast_redirect_out;
	out->u_data.redirect_out.cmd = command2;
	out->u_data.redirect_out.next = NULL;
	out->u_data.redirect_out.outfile = "newfile";
	out->u_data.redirect_out.tag = 1;

	t_ast *heredoc2 = malloc(sizeof(t_ast));
	heredoc2->u_data.redirect_out.outfile = "test2";
	heredoc2->u_data.redirect_out.cmd = NULL;
	heredoc2->type = ast_redirect_out;
	heredoc2->u_data.redirect_out.tag = 2;

	t_ast *heredoc3 = malloc(sizeof(t_ast));
	heredoc3->u_data.redirect_out.outfile = "test3";
	heredoc3->u_data.redirect_out.cmd = command2;
	heredoc3->type = ast_redirect_out;
	heredoc3->u_data.redirect_out.tag = 1;

	heredoc1->u_data.heredoc.next = heredoc2;
	heredoc2->u_data.redirect_out.next = heredoc3;
	heredoc3->u_data.redirect_out.next = NULL;
	in->u_data.redirect_in.next = NULL;
	//wc -l << dd > test2 > test3 < input 

	if (signal(SIGINT, handler) == SIG_ERR)
	{
		perror("signal");
		exit(1);
	}
	while (1)
	{
		run = 0;
		input = NULL;
		input = readline("minishell>");
		add_history(input);
		if (!input && run == 0)
		{
			write(1, "exit\n", 6);
			exit(0);
		}
		execute_commands(heredoc1, &envlst);
	}
}