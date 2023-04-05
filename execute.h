/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlektaib <mlektaib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 03:19:15 by mlektaib          #+#    #+#             */
/*   Updated: 2023/04/05 03:24:42 by mlektaib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H
# include "ast.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <sys/wait.h>

int	create_pipe(t_ast *node);
int	execute_redirect(t_ast *node);
int	execute_heredoc(t_ast *node);
int	execute_subshell(t_ast *node);
int	execute_commands(t_ast *node);
#endif