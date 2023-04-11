/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlektaib <mlektaib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 21:20:44 by mlektaib          #+#    #+#             */
/*   Updated: 2023/04/11 01:32:32 by mlektaib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

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

	end = 0;
	while (node && node->type == ast_heredoc)
	{
		end = check_last_heredoc(node);
		buffer = readline("heredoc> ");
		if (!buffer)
			break;
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
	return (node);
}

void	open_tmp_file(t_ast *node, int *infile_fd)
{
	int	open_flags;
	int	file_flags;

	open_flags = 0;
	file_flags = 0;
	open_flags = O_WRONLY | O_CREAT | O_TRUNC;
	file_flags = 0633;
	*infile_fd = open(node->u_data.heredoc.tmp, open_flags, file_flags);
	if (*infile_fd == -1)
	{
		perror(node->u_data.heredoc.tmp);
		return ;
	}
	open_flags = O_WRONLY | O_CREAT | O_APPEND;
	*infile_fd = open(node->u_data.heredoc.tmp, open_flags, file_flags);
	if (*infile_fd == -1)
	{
		perror(node->u_data.heredoc.tmp);
		return ;
	}
}
