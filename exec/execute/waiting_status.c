/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waiting_status.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlektaib <mlektaib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 16:44:30 by mlektaib          #+#    #+#             */
/*   Updated: 2023/06/23 13:29:51 by mlektaib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

extern t_global	g_global;

int	simple_command_es(int pid)
{
	int	status;

	status = 0;
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status))
		status = 130;
	else if (WIFEXITED(status))
		status = WEXITSTATUS(status);
	g_global.run = 0;
	return (status);
}

int	commnad_fd_es(int pid, int infile_fd, int outfile_fd)
{
	int	status;

	status = 0;
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status))
		status = 130;
	else if (WIFEXITED(status))
		status = WEXITSTATUS(status);
	if (infile_fd != STDIN_FILENO)
		close(infile_fd);
	if (outfile_fd != STDOUT_FILENO)
		close(outfile_fd);
	g_global.run = 0;
	return (status);
}
