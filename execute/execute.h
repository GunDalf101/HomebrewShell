/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlektaib <mlektaib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 03:19:15 by mlektaib          #+#    #+#             */
/*   Updated: 2023/04/08 20:21:57 by mlektaib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H
# include "../ast/ast.h"
# include "../commands/commands.h"
# include "../gnl/get_next_line.h"
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <unistd.h>
# include <unistd.h>

int	create_pipe(t_ast *node, t_env **env);
int	execute_redirect_out(t_ast *node, t_env **env);
int	execute_redirect_in(t_ast *node, t_env **env);
int	execute_heredoc(t_ast *node, t_env **env);
int	execute_subshell(t_ast *node, t_env **env);
int	execute_imp_commands(t_ast *node, t_env **env);
int	execute_commands(t_ast *node, t_env **env);
int	execute_simple_command_fd(t_ast *node, t_env **env, int infile_fd,
		int outfile_fd);
int	check_cmd(t_ast *node, t_env *env);
int	execute_redirect_heredoc(t_ast *node, t_env **env);
int	generate_rand(void);
#endif