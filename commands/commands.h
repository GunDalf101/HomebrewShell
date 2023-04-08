/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlektaib <mlektaib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 21:21:26 by mlektaib          #+#    #+#             */
/*   Updated: 2023/04/08 21:21:27 by mlektaib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDS_H
# define COMMANDS_H

# include "../ast/ast.h"
# include "../env/env.h"
# include <string.h>
int		exportcmd(t_env *head);
int		exportadd(t_env **head, t_ast *node);
int		envcmd(t_env *head);
int		unsetcmd(t_env **head, t_ast *node);
int		check_key(char *key);
int		pwd(void);
char	*return_pwd(void);
int		cd(t_ast *node, t_env **env);
int		echo(t_ast *node);
int		exportadd_for_cd(t_env **head, t_env *new);
#endif