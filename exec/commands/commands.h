/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlektaib <mlektaib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 21:21:26 by mlektaib          #+#    #+#             */
/*   Updated: 2023/07/15 06:33:27 by mlektaib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDS_H
# define COMMANDS_H

# include "../../parsing_realm/ast/ast.h"
# include "../env/env.h"
# include <string.h>
# include <sys/stat.h>
# include <errno.h>
# define RLTVERROR "cd: error retrieving current directory: \
getcwd: cannot access parent directories: No such file or directory"

typedef struct s_export
{
	int		size;
	char	**env;
	int		i;
	char	*key;
	char	*value;
	int		l;
}	t_export;

typedef struct s_cd
{
	char	*stack[4096];
	int		top;
	char	**tokens;
	int		pathlength;
	char	*path;
	char	*tmp;
}	t_cd;

int		exportcmd(t_env *head);
void	add_to_env(t_env **head, t_env *new);
void	print_env(t_env *tmp);
int		exportadd(t_env **head, t_ast *node);
int		envcmd(t_env *head);
int		unsetcmd(t_env **head, t_ast *node);
int		check_key(char *key);
int		pwd(t_env **env);
char	*return_pwd(void);
int		cd(t_ast *node, t_env **env);
int		echo(t_ast *node);
int		exportadd_for_cd(t_env **head, t_env *new);
void	assign_ranks(t_env *head, int *size);
void	sort_env(char **table, int size);
void	free_env(char **env, int size);
int		a_relative_path(char *str);
char	*get_tmp_relative(t_ast *node, t_env **env);
void	export_init(t_export *vars, t_env *head);
void	free_env_node(t_env *new, char *tmpvalue);
int		_unsetenv(char *deleted, t_env **head);
void	rebuild_cmd_node(t_ast *node, t_env **env, int f);
char	*converttoparent(char	*path);
int		to_dir(t_ast *node, t_env **env);
#endif