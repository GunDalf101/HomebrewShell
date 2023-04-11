/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlektaib <mlektaib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 21:20:28 by mlektaib          #+#    #+#             */
/*   Updated: 2023/04/11 01:28:13 by mlektaib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <signal.h>

int		run;
char	*input;
void	handler(int sig)
{
	if (run == 0)
	{
		write(STDOUT_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if(run== 1)
		write(STDOUT_FILENO, "\n", 1);
	
}

int	main(int argc, char *argv[], char **env)
{
	run = 0;
	rl_catch_signals = 0;
	if (signal(SIGINT, handler) == SIG_ERR)
	{
		perror("signal");
		exit(1);
	}

	t_env *envlst = load_env(env);

	t_env *tmp;

	char *command2_args[] = {"wc","-l", NULL};
	t_ast *command2 = add_new_cmd("wc", command2_args, 2, ast_cmd);
	t_ast *heredoc1 = add_new_heredoc("dd", command2);
	

	
	while (1)
	{
		char *heredoctmp = ft_strjoin("/tmp/heredoc", ft_itoa(generate_rand()));
		heredoc1->u_data.heredoc.tmp =heredoctmp;
		input = NULL;
		input = readline("minishell>");
		add_history(input);
		if (!input)
		{
			write(1, "exit\n", 6);
			exit(0);
		}
		execute_commands(heredoc1, &envlst);
		unlink(heredoctmp);
	}
}