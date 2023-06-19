/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbennani <mbennani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 03:30:56 by mlektaib          #+#    #+#             */
/*   Updated: 2023/05/14 21:06:15 by mbennani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

extern int	g_run;
extern int	g_fd[2];

int	get_subshell_exit_status(t_ast *node, int pid)
{
	int status;
	(void)node;
    waitpid(pid, &status, 0);
	g_run = 0;
    if (WIFEXITED(status)) 
        return WEXITSTATUS(status);
    else if (WIFSIGNALED(status)) 
        return 1;
	return 0;
}
int execute_subshell(t_ast *node, t_env **env) {
    pid_t pid = fork();
	g_run = 1;
    if (pid == -1)
	{
        perror("fork");
        return -1;
    } 
	else if (pid == 0) 
	{
		signal(SIGINT, command_sig);
        int result = execute_commands(node->u_data.subshell.child, env);
        exit(result);
    } 
	else 
	{
        return get_subshell_exit_status(node, pid);
    }
}