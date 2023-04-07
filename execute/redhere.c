/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redhere.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlektaib <mlektaib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 03:21:46 by mlektaib          #+#    #+#             */
/*   Updated: 2023/04/06 23:12:37 by mlektaib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

int	execute_redirect(t_ast *node,t_env **env)
{
	int	open_flags;
	int	file_flags;
	int	file_fd;

	if (node->u_data.redirect.fd == STDOUT_FILENO)
	{
		open_flags = O_WRONLY | O_CREAT | O_TRUNC;
		file_flags = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP;
	}
	else
	{
		open_flags = O_RDONLY;
		file_flags = S_IRUSR | S_IRGRP | S_IROTH;
	}
	file_fd = open(node->u_data.redirect.path, open_flags, file_flags);
	if (file_fd == -1)
	{
		perror(node->u_data.redirect.path);
		exit(1);
	}
	dup2(file_fd, node->u_data.redirect.fd);
	close(file_fd);
	return (execute_commands(node->u_data.redirect.child,env));
}

void	heredoc_reading_input(t_ast *node, int pipefd[2])
{
	char	*buffer;

	close(pipefd[0]);
	while (1)
	{
		write(0, "heredoc>", 9);
		buffer = readline("");
		if (buffer == NULL)
			exit(1);
		if (strncmp(buffer, node->u_data.heredoc.delimiter,
				strlen(node->u_data.heredoc.delimiter)) == 0
			&& strlen(node->u_data.heredoc.delimiter) == strlen(buffer))
		{
			free(buffer);
			break ;
		}
		if (write(pipefd[1], buffer, strlen(buffer)) == -1)
			exit(1);
		if (write(pipefd[1], "\n", 1) == -1)
			exit(1);
		free(buffer);
	}
	close(pipefd[1]);
	exit(0);
}

int	execute_heredoc(t_ast *node,t_env **env)
{
	int		pipefd[2];
	int		status;
	pid_t	pid;

	if (pipe(pipefd) == -1)
		exit(1);
	pid = fork();
	if (pid == -1)
		exit(1);
	else if (pid == 0)
		heredoc_reading_input(node, pipefd);
	else
	{
		close(pipefd[1]);
		dup2(pipefd[0], STDIN_FILENO);
		execute_commands(node->u_data.heredoc.child,env);
		close(pipefd[0]);
		waitpid(pid, &status, 0);
	}
	return (status);
}
