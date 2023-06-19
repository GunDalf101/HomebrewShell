/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbennani <mbennani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 03:20:19 by mlektaib          #+#    #+#             */
/*   Updated: 2023/06/19 14:08:56 by mbennani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
extern int g_fd[2];


int create_right_child(t_ast *node, int pipefd[2], int left_pid, t_env **env)
{
    int right_pid;
    int status;

    status = 0;
    right_pid = fork();
    if (right_pid == -1)
        exit(1);
    else if (right_pid == 0)
    {
        close(pipefd[1]);
        dup2(pipefd[0], STDIN_FILENO);
        close(pipefd[0]);
        status = execute_commands(node->u_data.operation.right, env);
        exit(status);
    }
    else
    {
        close(pipefd[0]);
        close(pipefd[1]); 
        waitpid(left_pid, &status, 0);
        waitpid(right_pid, &status, 0);
        return status;
    }
}

int create_pipe(t_ast *node, t_env **env)
{
    int pipefd[2];
    int left_pid;
    int status;

    status = 0;
    if (pipe(pipefd) == -1)
        exit(1);
    left_pid = fork();
    if (left_pid == -1)
        exit(1);
    else if (left_pid == 0)
    {
        close(pipefd[0]);
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[1]);
        status = execute_commands(node->u_data.operation.left, env);
        exit(status);
    }
    else
        return create_right_child(node, pipefd, left_pid, env);
}