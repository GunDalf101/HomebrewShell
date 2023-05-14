/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbennani <mbennani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 21:21:26 by mlektaib          #+#    #+#             */
/*   Updated: 2023/05/14 18:18:05 by mbennani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDS_H
# define COMMANDS_H

# include "../../parsing_realm/ast/ast.h"
# include "../env/env.h"
# include <string.h>

int		exportcmd(t_env *head);
void	print_env(t_env *tmp);
int		exportadd(t_env **head, t_ast *node);
int		envcmd(t_env *head);
int		unsetcmd(t_env **head, t_ast *node);
int		check_key(char *key);
int		pwd(void);
char	*return_pwd(void);
int		cd(t_ast *node, t_env **env);
int		echo(t_ast *node);
int		exportadd_for_cd(t_env **head, t_env *new);
void	assign_ranks(t_env *head, int *size);
void	sort_env(char **table, int size);
void	free_env(char **env, int size);

#endif