/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbennani <mbennani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 01:24:47 by mlektaib          #+#    #+#             */
/*   Updated: 2023/06/22 04:43:38 by mbennani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H
# include "../../exec/env/env.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_ast			t_ast;
enum							e_ast_type
{
	ast_cmd,
	ast_imp,
	ast_pipe,
	ast_redirect_out,
	ast_heredoc,
	ast_redirect_in,
	ast_and,
	ast_or,
	ast_subshell,
	ast_subshell_end,
};

enum							e_bool
{
	FALSE,
	TRUE
};

enum							e_rval
{
	SUCCESS,
	FAILURE
};

struct							s_cmd
{
	char						*cmd;
	char						**args;
	int							arg_count;
};

struct							s_operation
{
	t_ast						*left;
	t_ast						*right;
};

struct							s_redirect_out
{
	char						*outfile;
	t_ast						*cmd;
	int							tag;
	t_ast						*next;
};

struct							s_redirect_in
{
	char						*infile;
	t_ast						*cmd;
	t_ast						*next;
};

struct							s_heredoc
{
	char						*delim;
	t_ast						*cmd;
	t_ast						*next;
	char						*tmp;
}								t_heredoc;

struct							s_exit
{
	int							status;
}								t_exit;

struct							s_and
{
	t_ast						*left;
	t_ast						*right;
};

struct							s_or
{
	t_ast						*left;
	t_ast						*right;
};

struct							s_subshell
{
	char						*reparsethis;
	t_ast						*child;
};

struct							s_ast
{
	enum e_ast_type				type;
	union
	{
		struct s_cmd			cmd;
		struct s_operation		operation;
		struct s_redirect_in	redirect_in;
		struct s_redirect_out	redirect_out;
		struct s_heredoc		heredoc;
		struct s_and			_and;
		struct s_or				_or;
		struct s_subshell		subshell;
		struct s_exit			exit;
		t_env					envadds;
	} u_data;
};

t_ast							*setting_redirection(t_ast **lexical_table,
									int counter);
t_ast							*parse_tree(t_ast **lexical_table);
t_ast							*add_new_cmd(char *cmd, char **args,
									int arg_count, enum e_ast_type type);
t_ast							*add_new_subshell(t_ast *child,
									char *reparsethis);
t_ast							*add_new_operation(enum e_ast_type type,
									t_ast *left, t_ast *right);
t_ast							*add_new_redirect_out(char *outfile, t_ast *cmd,
									int tag);
t_ast							*add_new_heredoc(char *delimiter, t_ast *child);
void							free_ast_node(t_ast *node);
t_ast							*add_new_redirect_in(char *infile, t_ast *cmd);
t_ast							*getting_the_root(t_ast **lexical_table, \
									int type, int counter);
t_ast							*setting_west_side(t_ast **lexical_table, \
									int counter);
t_ast							*setting_east_side(t_ast **lexical_table, \
									int counter);
t_ast							*setting_command_redir(t_ast **lexical_table, \
									int counter);
t_ast							*parse_tree(t_ast **lexical_table);
t_ast							*setting_subshell(t_ast **lexical_table, \
									int counter);
t_ast							*setting_redirection(t_ast **lexical_table, \
									int counter);
#endif