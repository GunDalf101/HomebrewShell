/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbennani <mbennani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 17:47:29 by mbennani          #+#    #+#             */
/*   Updated: 2023/05/14 18:25:55 by mbennani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "parsing_realm/ast/ast.h"
# include "exec/minishellexec.h"
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
# include <unistd.h>

enum				e_bool
{
	FALSE,
	TRUE
};
enum				e_rval
{
	SUCCESS,
	FAILURE
};

#endif