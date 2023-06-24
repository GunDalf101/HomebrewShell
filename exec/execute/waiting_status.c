/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waiting_status.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlektaib <mlektaib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 16:44:30 by mlektaib          #+#    #+#             */
/*   Updated: 2023/06/24 11:32:21 by mlektaib         ###   ########.fr       */
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

// void	pointers_back(t_ast *new)
// {
// 	t_pointers	*tmp;

// 	t_pointers	*newptr;
// 	newptr = malloc(sizeof(t_pointers));
// 	newptr->p = new;
// 	tmp = g_global.pointers;
// 	if (g_global.pointers == NULL)
// 		g_global.pointers = newptr;
// 	else
// 	{
// 		while (tmp->next != NULL)
// 			tmp = tmp->next;
// 		tmp->next = newptr;
// 	}
// 	newptr->next = NULL;
// }

// void	pointers_free(void)
// {
// 	t_pointers	*tmp;
// 	t_pointers	*next;

// 	tmp = g_global.pointers;
// 	next = NULL;
// 	while(tmp)
// 	{
// 		next = tmp->next;
// 		free_cmd_node(tmp->p);
// 		tmp = next;
// 	}
// 	g_global.pointers = NULL;
// }