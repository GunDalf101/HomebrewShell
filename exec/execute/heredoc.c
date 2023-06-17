/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlektaib <mlektaib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 21:20:44 by mlektaib          #+#    #+#             */
/*   Updated: 2023/06/09 12:05:10 by mlektaib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishellexec.h"
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

t_ast	*read_heredoc(t_ast *node, t_fd *fd, int *end, char **totalbuffer)
{
	char	*buffer;
	char	*tmp;
	
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
			free(buffer);
			if (!node || node->type != ast_heredoc)
				continue ;
		}
		else if (*end)
		{
			tmp = buffer;
			buffer = ft_strjoin(buffer, "\n");
			free(tmp);
			tmp = *totalbuffer;
			*totalbuffer = ft_strjoin(*totalbuffer, buffer);
			free(tmp);
		}
	}
	return (node);
}


t_ast	*heredoc_handler(t_ast *node, t_fd *fd)
{
	int		end;
	char	*totalbuffer;
	t_ast	*tmp;

	fd->dupstdin = handle_dupstdin_and_sig();
	tmp = node;
	end = 0;
	g_run = 1;
	totalbuffer = ft_strdup("");
	node = read_heredoc(node, fd, &end, &totalbuffer);
	if (g_run != 130)
		write_in_heredoc_file(totalbuffer, tmp, fd);
	else 
		free(totalbuffer);
	signal(SIGINT, signal_hand);
	return (node);
}
