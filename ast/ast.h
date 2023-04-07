/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlektaib <mlektaib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 01:24:47 by mlektaib          #+#    #+#             */
/*   Updated: 2023/04/07 01:40:57 by mlektaib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H
#include<unistd.h>
#include <stdlib.h>
#include "../env/env.h"
typedef struct s_ast		t_ast;
enum						e_ast_type
{
	ast_cmd,
	ast_imp,
	ast_pipe,
	ast_redirect,
	ast_heredoc,
	ast_and,
	ast_or,
	ast_subshell,
	ast_exit,
};

struct						s_cmd
{
	char					*cmd;
	char					**args;
	int						arg_count;
};

struct						s_operation
{
	t_ast					*left;
	t_ast					*right;
};

struct						s_redirect
{
	int						fd;
	char					*path;
	t_ast					*child;
	int						tag;
};

struct						s_heredoc
{
	char					*delimiter;
	t_ast					*child;
};

struct						s_and
{
	t_ast					*left;
	t_ast					*right;
};

struct						s_or
{
	t_ast					*left;
	t_ast					*right;
};

struct						s_subshell
{
	t_ast					*child;
};

struct						s_ast
{
	enum e_ast_type			type;
	union
	{
		struct s_cmd		cmd;
		struct s_operation	operation;
		struct s_redirect	redirect;
		struct s_heredoc	heredoc;
		struct s_and		_and;
		struct s_or			_or;
		struct s_subshell	subshell;
		t_env				envadds;
	} u_data;
};
t_ast						*add_new_cmd(char *cmd, char **args, int arg_count,enum e_ast_type type);
t_ast						*add_new_subshell(t_ast *child);
t_ast						*add_new_operation(enum e_ast_type type,
								t_ast *left, t_ast *right);
t_ast						*add_new_redirect(int fd, char *path, t_ast *child,
								int tag);
t_ast						*add_new_heredoc(char *delimiter, t_ast *child);
#endif