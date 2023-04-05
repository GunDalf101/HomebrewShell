/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlektaib <mlektaib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 03:25:39 by mlektaib          #+#    #+#             */
/*   Updated: 2023/04/05 03:32:54 by mlektaib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "execute.h"

int	execute_simple_command(t_ast *node)
{
	int		status;
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(1);
	}
	else if (pid == 0)
	{
		execvp(node->u_data.cmd.cmd, node->u_data.cmd.args);
		perror(node->u_data.cmd.cmd);
		exit(1);
	}
	else
	{
		waitpid(pid, &status, 0);
		return (status);
	}
}

int	execute_and(t_ast *node)
{
	int	status;
	int	left_status;

	left_status = execute_commands(node->u_data.operation.left);
	if (left_status == 0)
		status = execute_commands(node->u_data.operation.right);
	else
		status = left_status;
	return (status);
}

int	execute_or(t_ast *node)
{
	int	status;
	int	left_status;

	left_status = execute_commands(node->u_data.operation.left);
	if (left_status != 0)
	{
		status = execute_commands(node->u_data.operation.right);
	}
	return (status);
}

int	execute_commands(t_ast *node)
{
	int	status;

	if (!node)
		return (0);
	status = 0;
	if (node->type == ast_cmd)
		status = execute_simple_command(node);
	else if (node->type == ast_pipe)
		status = create_pipe(node);
	else if (node->type == ast_redirect)
		status = execute_redirect(node);
	else if (node->type == ast_heredoc)
		status = execute_heredoc(node);
	else if (node->type == ast_subshell)
		status = execute_subshell(node);
	else if (node->type == ast_and)
		status = execute_and(node);
	else if (node->type == ast_or)
		status = execute_or(node);
	return (status);
}

// int	main(void)
// {
// 	char *command1_args[] = {"ls", NULL};
// 	t_ast *command1 = add_new_cmd("ls", command1_args, 2);

// 	char *command2_args[] = {"grep", "foo", NULL};
// 	t_ast *command2 = add_new_cmd("grep", command2_args, 2);

// 	t_ast *pipe1 = add_new_operation(ast_pipe, command1, command2);

// 	t_ast *subshell1 = add_new_subshell(pipe1);

// 	char *command3_args[] = {"wc", "-l", NULL};
// 	t_ast *command3 = add_new_cmd("wc", command3_args, 2);
// 	t_ast *herdoc = add_new_heredoc("dsf", command3);

// 	t_ast *pipe2 = add_new_operation(ast_pipe, command2, herdoc);

// 	char *command4_args[] = {"sort", NULL};
// 	t_ast *command4 = add_new_cmd("sort", command4_args, 1);

// 	t_ast *sort_output = add_new_redirect(1, "output.txt", command4, 1);

// 	t_ast *pipe3 = add_new_operation(ast_pipe, herdoc, sort_output);

// 	execute_commands(pipe3);

// 	return (0);
// }