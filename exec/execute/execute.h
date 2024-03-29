/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlektaib <mlektaib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 03:19:15 by mlektaib          #+#    #+#             */
/*   Updated: 2023/07/16 05:01:47 by mlektaib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H
# include "../../parsing_realm/ast/ast.h"
# include "../../parsing_realm/lexical_analyzer/lexing_lexer.h"
# include "../commands/commands.h"
# include <dirent.h>
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
	int				infile_fd;
	int				outfile_fd;
	int				error;
	int				dupstdin;
}					t_fd;

typedef struct s_global
{
	unsigned char	exit_status;
	int				run;
}					t_global;

typedef struct s_expand
{
	char			*str;
	int				len;
	int				i;
	int				j;
	int				start;
	int				end;
	int				inside_single;
	int				inside_double;
	char			*var;
	char			*value;
	int				s;

}					t_expand;

typedef struct s_herevars
{
	char			*buffer;
	char			*tmp;
	int				expand;
	int				end;
	int				i;
	int				s;
}					t_herevars;

typedef struct s_wild
{
	DIR				*dir;
	struct dirent	*entry;
	int				i;
	char			*result;
	char			*pattern;
}					t_wild;

int					create_pipe(t_ast *node, t_env **env);
int					execute_subshell(t_ast *node, t_env **env);
int					execute_imp_commands(t_ast *node, t_env **env, int k);
int					execute_commands(t_ast *node, t_env **env, int k);
int					execute_simple_command_fd(t_ast *node, t_env **env,
						int infile_fd, int outfile_fd);
int					check_cmd(t_ast *node, t_env *env);
int					execute_redirect_heredoc(t_ast *node, t_env **env);
int					generate_rand(void);
t_ast				*create_red_files(t_ast *node, t_fd *fd, t_env *env);
t_ast				*getting_infile_fd(t_ast *node, t_fd *fd, t_env *env);
void				open_tmp_file(t_ast *node, t_fd *fd);
t_ast				*heredoc_handler(t_ast *node, t_fd *fd, t_env **env);
void				execute_command_fd(t_ast *node, t_env **env, int infile_fd,
						int outfile_fd);
int					find_command_path(t_ast *node, t_env *env);
void				exec_cmd(t_ast *node, t_env **env);
void				heredoc_sig(int sig);
void				write_heredoc_file(char *buffer, t_ast *node);
int					check_last_heredoc(t_ast *node);
void				set_imp_commands(t_ast *node);
int					get_subshell_exit_status(t_ast *node, int pid);
t_ast				*expand(t_ast *node, t_env **env);
char				*quotes_remover(char *str);
char				*heredoc_expansion(char *str, t_env *env);
char				*quotes_busters(char *str, t_env *env, int flag);
int					execute_all_heredocs(t_ast *node, t_env **env);
int					execute_heredocs(t_ast *node, t_env **env);
int					exitcmd(t_ast *node, int k);
void				replace_env(t_expand *expand);
void				expand_start(t_expand *expand, t_env *env);
int					commnad_fd_es(int pid, int infile_fd, int outfile_fd);
int					simple_command_es(int pid);
void				expand_intialize(t_expand *expand, char *str);
t_ast				*read_heredoc(t_ast *node, t_fd *fd, char **totalbuffer,
						t_env **env);
t_ast				*open_heredoc_tmp(t_fd *fd, t_ast *node);
void				fd_init(t_fd *fd);
void				dupping_fds(int infile_fd, int outfile_fd);
void				close_fds(t_fd *fd);
t_ast				*get_cmd_node(t_ast *node);
void				redup_stdin(t_fd *fd);
t_ast				*getting_fds_for_red(t_fd *fd, t_ast *node, t_env **env);
t_ast				*rebuild_node(t_ast *node);
t_ast				*expander(t_ast *node, t_env **env, int f);
void				shift_args(t_ast *node, int i);
void				wildcard_dealer(t_ast *node);
void				pointers_free(void);
void				pointers_back(t_ast *new);
char				*wild_redirection(char *pattern);
int					match_pattern(char *pattern, char *text);
int					is_wild(char *str);
int					wildcount(char **args, int arg_count);
void				wild_init(t_wild *wild, char *pattern);
void				args_remake(t_ast *node);
void				expand_command(t_ast *node, t_env **env, int f);
void				update_command(t_ast *node, char *command);
char				**create_fullargs_array(char **newargs, int arg_count);
void				append_remaining_args(t_ast *node, char **fullargs,
						int count);
void				update_arg_count(t_ast *node);
void				quote_on_quote(t_expand *expand);
void				expand_end(t_expand *expand, t_env *env);

#endif