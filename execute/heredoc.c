/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlektaib <mlektaib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 21:20:44 by mlektaib          #+#    #+#             */
/*   Updated: 2023/04/08 21:20:45 by mlektaib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

void heredoc_reading_input(t_ast *node, int pipefd[2]) {
    char *buffer;
	int end = 0;

    close(pipefd[0]);
    while (node && node->type == ast_heredoc) {
		buffer = NULL;
        buffer = readline("heredoc>");
        if (buffer == NULL) {
            exit(1);
        }
        if (strcmp(buffer, node->u_data.heredoc.delim) == 0) {
				node = node->u_data.heredoc.next;
				if(!node || node->type != ast_heredoc)
					break;
        }
        if (end) {
            if (write(pipefd[1], buffer, strlen(buffer)) == -1) {
                exit(1);
            }
            if (write(pipefd[1], "\n", 1) == -1) {
                exit(1);
            }
        }
		if(!node->u_data.heredoc.next || node->type != ast_heredoc)
			end = 1;
        free(buffer);
    }
    close(pipefd[1]);
    exit(0);
}

int execute_heredoc(t_ast *node, t_env **env) {
    int pipefd[2];
    int status = 0;
    pid_t pid;

        if (pipe(pipefd) == -1)
            exit(1);
        pid = fork();
        if (pid == -1)
            exit(1);
        else if (pid == 0) {
            heredoc_reading_input(node, pipefd);
        } else {
            close(pipefd[1]); 
            dup2(pipefd[0], STDIN_FILENO);
            execute_commands(node->u_data.heredoc.cmd, env);
            close(pipefd[0]);
            waitpid(pid, &status, 0);
        }
    return status;
}