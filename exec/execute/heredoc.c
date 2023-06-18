/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbennani <mbennani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 21:20:44 by mlektaib          #+#    #+#             */
/*   Updated: 2023/06/18 15:57:48 by mbennani         ###   ########.fr       */
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

t_ast	*read_heredoc(t_ast *node, t_fd *fd, int *end, char **totalbuffer,t_env **env)
{
	char	*buffer;
	char	*tmp;
	int		expand;
	int i = 0;
	int s = 0;
	
	while (node && node->type == ast_heredoc)
	{
		if (s == 0)
		{
			expand = 0;
			i = 0;
			while(node->u_data.heredoc.delim[i])
			{
				if (node->u_data.heredoc.delim[i] == '\'' || node->u_data.heredoc.delim[i] == '\"')
					expand = 1;
				i++;
			}
			s = 1;
		}
		buffer = NULL;
		*end = check_last_heredoc(node);
		buffer = readline("heredoc> ");
		if (!buffer)
		{
			s = 0;
			redup_stdin(fd);
			break ;
		}
		else if (strcmp(buffer, quotes_remover(node->u_data.heredoc.delim)) == 0)
		{
			node = node->u_data.heredoc.next;
			s = 0;
			free(buffer);
			if (!node || node->type != ast_heredoc)
				continue ;
		}
		else if (*end)
		{
			if (expand==0)
				buffer = heredoc_expansion(buffer,*env);
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


t_ast	*heredoc_handler(t_ast *node, t_fd *fd,t_env **env)
{
	int		end;
	char	*totalbuffer;
	t_ast	*tmp;

	fd->dupstdin = handle_dupstdin_and_sig();
	tmp = node;
	end = 0;
	g_run = 1;
	totalbuffer = ft_strdup("");
	node = read_heredoc(node, fd, &end, &totalbuffer,env);
	if (g_run != 130)
		write_in_heredoc_file(totalbuffer, tmp, fd);
	else 
		free(totalbuffer);
	signal(SIGINT, signal_hand);
	return (node);
}
