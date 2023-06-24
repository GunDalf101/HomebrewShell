/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_read.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbennani <mbennani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 16:56:55 by mlektaib          #+#    #+#             */
/*   Updated: 2023/06/24 21:09:03 by mbennani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

void	heredoc_vars_init(t_herevars *vars)
{
	vars->buffer = NULL;
	vars->tmp = NULL;
	vars->expand = 0;
	vars->end = 0;
	vars->i = 0;
	vars->s = 0;
}

void	heredoc_expand_checker(t_herevars *vars, t_ast *node)
{
	vars->expand = 0;
	vars->i = 0;
	while (node->u_data.heredoc.delim[vars->i])
	{
		if (node->u_data.heredoc.delim[vars->i] == '\''
			|| node->u_data.heredoc.delim[vars->i] == '\"')
			vars->expand = 1;
		vars->i++;
	}
	vars->s = 1;
}

void	write_in_tmp(t_herevars *vars, char **totalbuffer, t_env **env)
{
	(void)env;
	if (vars->expand == 0)
		vars->buffer = heredoc_expansion(vars->buffer, *env);
	vars->tmp = vars->buffer;
	vars->buffer = ft_strjoin(vars->buffer, "\n");
	free(vars->tmp);
	vars->tmp = *totalbuffer;
	*totalbuffer = ft_strjoin(*totalbuffer, vars->buffer);
	free(vars->buffer);
	free(vars->tmp);
}

t_ast	*jump_to_next(t_herevars *vars, t_ast *node)
{
	node = node->u_data.heredoc.next;
	vars->s = 0;
	free(vars->buffer);
	return (node);
}

t_ast	*read_heredoc(t_ast *node, t_fd *fd, char **totalbuffer, t_env **env)
{
	t_herevars	vars;

	heredoc_vars_init(&vars);
	while (node && node->type == ast_heredoc)
	{
		if (vars.s == 0)
			heredoc_expand_checker(&vars, node);
		vars.buffer = NULL;
		vars.end = check_last_heredoc(node);
		vars.buffer = readline("> ");
		if (!vars.buffer)
		{
			vars.s = 0;
			redup_stdin(fd);
			break ;
		}
		else if (ft_strcmp(vars.buffer,
				quotes_remover(node->u_data.heredoc.delim)) == 0)
			node = jump_to_next(&vars, node);
		else if (vars.end)
			write_in_tmp(&vars, totalbuffer, env);
	}
	close(fd->dupstdin);
	return (node);
}
