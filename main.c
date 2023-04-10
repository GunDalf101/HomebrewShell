/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlektaib <mlektaib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 21:20:28 by mlektaib          #+#    #+#             */
/*   Updated: 2023/04/10 03:10:30 by mlektaib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <signal.h>

char	*input;
void	handler(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

int	main(int argc, char *argv[], char **env)
{
	//  if (signal(SIGINT, handler) == SIG_ERR) {
	//     perror("signal");
	//     exit(1);
	// }
	// // while (1)
	// // {
	// 	input = NULL;
	// 	input = readline("minishell>");
	// 	printf("input  == %s\n",input);
	// 	add_history(input);

	// 	if(!input)
	// 	{
	// 		write(1,"\n",1);
	// 		write(1,"exit\n",6);
	// 		exit(130);
	// 	}

	// }

	char *heredoctmp = ft_strjoin("/tmp/heredoc", ft_itoa(generate_rand()));
	t_env *envlst = load_env(env);
	t_env *tmp;

	char *command2_args[] = {"export", "adtest=hdsgd", NULL};
	t_ast *command2 = add_new_cmd("export", command2_args, 2, ast_imp);

	char *command3_args[] = {"export", "test=sghdsf", NULL};
	t_ast *command3 = add_new_cmd("export", command3_args, 2, ast_imp);

	char *command4_args[] = {"export", NULL};
	t_ast *command4 = add_new_cmd("export", command4_args, 1, ast_imp);

	execute_commands(command2, &envlst);
	execute_commands(command3, &envlst);
	execute_commands(command4, &envlst);
	unlink(heredoctmp);
}