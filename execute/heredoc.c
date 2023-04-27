/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlektaib <mlektaib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 21:20:44 by mlektaib          #+#    #+#             */
/*   Updated: 2023/04/27 11:15:07 by mlektaib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "execute.h"

extern int	run;

void	her_handler(int sig)
{
	exit(130);
}
int	check_last_heredoc(t_ast *node)
{
	if (node->u_data.heredoc.next || !node->u_data.heredoc.next)
	{
		if (!node->u_data.heredoc.next
			|| node->u_data.heredoc.next->type != ast_heredoc)
			return (1);
	}
	return (0);
}

void	write_heredoc_file(char *buffer, int infile_fd)
{
	if (write(infile_fd, buffer, strlen(buffer)) == -1)
	{
		perror("write");
		exit(1);
	}
	if (write(infile_fd, "\n", 1) == -1)
	{
		perror("write");
		exit(1);
	}
}

t_ast	*heredoc_handler(t_ast *node, int infile_fd)
{
	char	*buffer;
	int		end;
	int		pid;
	int		status;

	end = 0;
	pid = fork();
	run = 1;
	if (pid == 0)
	{
		signal(SIGINT, her_handler);
		while (node && node->type == ast_heredoc)
		{
			end = check_last_heredoc(node);
			buffer = readline("heredoc> ");
			if (!buffer)
				break ;
			if (strcmp(buffer, node->u_data.heredoc.delim) == 0)
			{
				node = node->u_data.heredoc.next;
				if (!node || node->type != ast_heredoc)
					continue ;
			}
			if (end)
				write_heredoc_file(buffer, infile_fd);
			free(buffer);
		}
		exit(0);
	}
	else
	{
		while (node && node->type == ast_heredoc)
			node = node->u_data.heredoc.next;
		waitpid(pid, &status, 0);
		run = 0;
		if (status)
			run = 130;
		return (node);
	}
	return (NULL);
}

void	open_tmp_file(t_ast *node, int *infile_fd)
{

	*infile_fd = open(node->u_data.heredoc.tmp, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (*infile_fd == -1)
	{
		perror(node->u_data.heredoc.tmp);
		return ;
	}
	close(*infile_fd);
	*infile_fd = open(node->u_data.heredoc.tmp, O_WRONLY | O_APPEND, 0777);
	if (*infile_fd == -1)
	{
		perror(node->u_data.heredoc.tmp);
		return ;
	}
}
