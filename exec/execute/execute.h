/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbennani <mbennani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 03:19:15 by mlektaib          #+#    #+#             */
/*   Updated: 2023/05/14 18:18:38 by mbennani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H
# include "../../parsing_realm/ast/ast.h"
# include "../commands/commands.h"
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_fd
{
	int	infile_fd;
	int	outfile_fd;
	int	error;
	int	dupstdin;
}		t_fd;

void	command_sig(int sig);
int		create_pipe(t_ast *node, t_env **env);
int		execute_subshell(t_ast *node, t_env **env);
int		execute_imp_commands(t_ast *node, t_env **env);
int		execute_commands(t_ast *node, t_env **env);
int		execute_simple_command_fd(t_ast *node, t_env **env, int infile_fd,
			int outfile_fd);
int		check_cmd(t_ast *node, t_env *env);
int		execute_redirect_heredoc(t_ast *node, t_env **env);
int		generate_rand(void);
t_ast	*create_red_files(t_ast *node, t_fd *fd);
t_ast	*getting_infile_fd(t_ast *node, t_fd *fd);
void	open_tmp_file(t_ast *node, t_fd *fd);
t_ast	*heredoc_handler(t_ast *node, t_fd *fd);
void	execute_command_fd(t_ast *node, t_env **env, int infile_fd,
			int outfile_fd);
int		find_command_path(t_ast *node, t_env *env);
void	exec_cmd(t_ast *node, t_env **env);
void	command_sig(int sig);
void	heredoc_sig(int sig);
void	write_heredoc_file(char *buffer, t_ast *node);
int		check_last_heredoc(t_ast *node);
#endif