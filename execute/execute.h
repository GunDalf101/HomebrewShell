/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlektaib <mlektaib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 03:19:15 by mlektaib          #+#    #+#             */
/*   Updated: 2023/04/06 23:15:48 by mlektaib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H
#include "../ast/ast.h"
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>


# include <readline/history.h>
# include <readline/readline.h>
# include <stdlib.h>
# include <sys/wait.h>
#include <string.h>
# include <unistd.h>
# include "../commands/commands.h"

int	create_pipe(t_ast *node,t_env **env);
int	execute_redirect(t_ast *node,t_env **env);
int	execute_heredoc(t_ast *node,t_env **env);
int	execute_subshell(t_ast *node,t_env **env);
int execute_imp_commands(t_ast *node,t_env **env);
int	execute_commands(t_ast *node,t_env **env);
#endif