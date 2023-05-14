/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlektaib <mlektaib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 21:20:44 by mlektaib          #+#    #+#             */
/*   Updated: 2023/05/14 15:37:30 by mlektaib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "execute.h"

extern int	g_run;

int	handle_dupstdin_and_sig(void)
{
	int	dupstdin;

	dupstdin = dup(0);
	if (dupstdin == -1)
	{
		perror("dup");
		return (-1);
	}
	signal(SIGINT, heredoc_sig);
	return (dupstdin);
}

void	write_in_heredoc_file(char *totalbuffer, t_ast *tmp, t_fd *fd)
{
	write_heredoc_file(totalbuffer, tmp);
	fd->infile_fd = open(tmp->u_data.heredoc.tmp, O_RDWR | O_EXCL, 0600);
	if (fd->infile_fd == -1)
	{
		perror(tmp->u_data.heredoc.tmp);
		fd->error = 1;
	}
}

void	redup_stdin(t_fd *fd)
{
	if (g_run == 130)
	{
		if (dup2(fd->dupstdin, 0) == -1)
		{
			perror("dup2");
			fd->error = 1;
		}
	}
}

void	read_heredoc(t_ast *node, t_fd *fd, int *end, char *totalbuffer)
{
	char	*buffer;

	while (node && node->type == ast_heredoc)
	{
		buffer = NULL;
		*end = check_last_heredoc(node);
		buffer = readline("heredoc> ");
		if (!buffer)
		{
			redup_stdin(fd);
			break ;
		}
		else if (strcmp(buffer, node->u_data.heredoc.delim) == 0)
		{
			node = node->u_data.heredoc.next;
			if (!node || node->type != ast_heredoc)
				continue ;
		}
		else if (*end)
		{
			buffer = ft_strjoin(buffer, "\n");
			totalbuffer = ft_strjoin(totalbuffer, buffer);
		}
		free(buffer);
	}
}

t_ast	*heredoc_handler(t_ast *node, t_fd *fd)
{
	char	*buffer;
	int		end;
	char	*totalbuffer;
	t_ast	*tmp;

	fd->dupstdin = handle_dupstdin_and_sig();
	tmp = node;
	end = 0;
	g_run = 1;
	totalbuffer = ft_strdup("");
	read_heredoc(node, fd, &end, totalbuffer);
	if (g_run != 130)
		write_in_heredoc_file(totalbuffer, tmp, fd);
	free(totalbuffer);
	signal(SIGINT, signal_hand);
	return (node);
}
