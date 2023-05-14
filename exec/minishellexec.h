/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishellexec.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbennani <mbennani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 01:49:32 by mlektaib          #+#    #+#             */
/*   Updated: 2023/05/14 20:50:10 by mbennani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELLEXEC_H
# define MINISHELLEXEC_H

# include "../parsing_realm/ast/ast.h"
# include "commands/commands.h"
# include "env/env.h"
# include "execute/execute.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

void	signal_hand(int signum);

#endif