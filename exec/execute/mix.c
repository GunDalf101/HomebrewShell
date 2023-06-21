/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mix.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbennani <mbennani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 21:20:47 by mlektaib          #+#    #+#             */
/*   Updated: 2023/06/19 15:14:12 by mbennani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

extern t_global	g_global;

void	fd_init(t_fd *fd)
{
	fd->error = 0;
	fd->infile_fd = 0;
	fd->outfile_fd = 1;
}

void execute_command_fd(t_ast *node, t_env **env, int infile_fd, int outfile_fd)
{
    signal(SIGINT, command_sig);

    if (infile_fd != STDIN_FILENO)
    {
        if (dup2(infile_fd, STDIN_FILENO) == -1)
        {
            perror("dup2");
            exit(1);
        }
        close(infile_fd);
    }

    if (outfile_fd != STDOUT_FILENO)
    {
        if (dup2(outfile_fd, STDOUT_FILENO) == -1)
        {
            perror("dup2");
            exit(1);
        }
        close(outfile_fd);
    }
    execve(node->u_data.cmd.cmd, node->u_data.cmd.args, lst_to_env(*env));
    perror(node->u_data.cmd.cmd);
    exit(1);
}


t_ast	*get_cmd_node(t_ast *node)
{
	t_ast	*cmd;

	cmd = NULL;
	if (node->type == ast_redirect_out)
		cmd = node->u_data.redirect_out.cmd;
	else if (node->type == ast_redirect_in)
		cmd = node->u_data.redirect_in.cmd;
	else if (node->type == ast_heredoc)
		cmd = node->u_data.heredoc.cmd;
	else if (node->type == ast_subshell)
		cmd = node->u_data.subshell.child;
	return (cmd);
}

int execute_subshell_fd(t_ast *node, t_env **env, int infile_fd, int outfile_fd)
{
    int pid;
    int subshell_status;

    pid = fork();
    if (pid == -1)
        exit(EXIT_FAILURE);
    if (pid == 0)
    {
        signal(SIGINT, command_sig);
        if (infile_fd != STDIN_FILENO)
        {
            if (dup2(infile_fd, STDIN_FILENO) == -1)
            {
                perror("dup2");
                exit(1);
            }
            close(infile_fd);
        }

        if (outfile_fd != STDOUT_FILENO)
        {
            if (dup2(outfile_fd, STDOUT_FILENO) == -1)
            {
                perror("dup2");
                exit(1);
            }
            close(outfile_fd);
        }
        subshell_status = execute_commands(node->u_data.subshell.child, env);
        exit(subshell_status);
    }
    if(infile_fd != STDIN_FILENO)
        close(infile_fd);
    if(outfile_fd != STDOUT_FILENO)
        close(outfile_fd);
    return get_subshell_exit_status(node, pid);
}


int	execute_redirect_heredoc(t_ast *node, t_env **env)
{
	t_fd	fd;
	t_ast	*cmd;

	cmd = NULL;
	fd_init(&fd);
	if (!fd.error)
		cmd = get_cmd_node(node);
	while (node && g_global.run != 130)
	{
		if (node->type == ast_redirect_out)
			node = create_red_files(node, &fd,*env);
		else if (node->type == ast_redirect_in)
			node = getting_infile_fd(node, &fd,*env);
		else if (node->type == ast_heredoc)
		{
            if(fd.infile_fd != STDIN_FILENO)
                close(fd.infile_fd);
			fd.infile_fd = open(node->u_data.heredoc.tmp, O_RDONLY | O_EXCL, 0666);
			node = node->u_data.heredoc.next;
		}
	}
	if (!fd.error && g_global.run != 130 && cmd && cmd->type == ast_cmd)
		return (execute_simple_command_fd(cmd, env, fd.infile_fd, fd.outfile_fd));
	else if (!fd.error && g_global.run != 130 && cmd && cmd->type == ast_subshell)
		return(execute_subshell_fd(cmd, env, fd.infile_fd, fd.outfile_fd));
    else
    {
        if(fd.infile_fd != STDIN_FILENO)
            close(fd.infile_fd);
        if(fd.outfile_fd != STDOUT_FILENO)
            close(fd.outfile_fd);
    }
    if(g_global.run == 130)
        return 130;
	return (0);
}


int	execute_heredocs(t_ast *node, t_env **env)
{
	t_fd	fd;
	t_ast	*cmd;

	cmd = NULL;
    cmd = get_cmd_node(node);
    if(cmd && cmd->type == ast_subshell)
        execute_all_heredocs(node->u_data.subshell.child, env);
    fd_init(&fd);
	while (node && g_global.run != 130)
	{
        g_global.run = 0;
		if (node->type == ast_redirect_out)
			node= node->u_data.redirect_out.next;
		else if (node->type == ast_redirect_in)
			node = node->u_data.redirect_in.next;
		else if (node->type == ast_heredoc)
		{
			char *tmp = ft_itoa(generate_rand());
            node->u_data.heredoc.tmp = ft_strjoin("/tmp/", tmp);
            free(tmp);
			open_tmp_file(node, &fd);
			node = heredoc_handler(node, &fd,env);
            if (fd.infile_fd != STDIN_FILENO)
                close(fd.infile_fd);
			if (!node || node->type != ast_heredoc)
				continue ;
			node = node->u_data.heredoc.next;
		}
	}
	return (g_global.run);
}