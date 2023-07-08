/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waiting_status.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbennani <mbennani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 16:44:30 by mlektaib          #+#    #+#             */
/*   Updated: 2023/07/08 18:40:03 by mbennani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

extern t_global	g_global;

int	simple_command_es(int pid)
{
	int	status;

	status = 0;
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status)) 
	{
			status = WTERMSIG(status);
			if (status == 2)
			{
				status = 130;
			}
	else if (status == 3)
		{
			ft_putendl_fd("Quit: 3", 1);
			status = 131;
		}
	}
	return (status);
}

int	commnad_fd_es(int pid, int infile_fd, int outfile_fd)
{
	int	status;

	status = 0;
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		status = WEXITSTATUS(status);
	if (infile_fd != STDIN_FILENO)
		close(infile_fd);
	if (outfile_fd != STDOUT_FILENO)
		close(outfile_fd);
	return (status);
}
