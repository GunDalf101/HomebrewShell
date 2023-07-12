/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbennani <mbennani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 04:36:07 by mbennani          #+#    #+#             */
/*   Updated: 2023/07/12 06:29:21 by mbennani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing101.h"
#include "ast.h"

// the function that handles the subshell AKA parenthesis
t_ast	*setting_subshell(t_ast **lexical_table, int counter);

void	trim_subshell_reparsethis(t_ast *subshell)
{
	char	*tmp;

	tmp = subshell->u_data.subshell.reparsethis;
	subshell->u_data.subshell.reparsethis = ft_strtrim(tmp, "()");
	free(tmp);
}

t_ast	*process_redirection(t_ast **lexical_table, int counter,
		t_ast *subshell)
{
	t_ast	*head;

	head = setting_redirection(lexical_table, counter);
	if (head->type == ast_heredoc)
		head->u_data.heredoc.cmd = subshell;
	else if (head->type == ast_redirect_out)
		head->u_data.redirect_out.cmd = subshell;
	else if (head->type == ast_redirect_in)
		head->u_data.redirect_in.cmd = subshell;
	return (head);
}

t_ast	*check_and_set_redirection(t_ast **lexical_table, int counter,
		t_ast *subshell)
{
	int		i;
	t_ast	*head;

	i = 0;
	head = NULL;
	while (lexical_table[counter] && lexical_table[counter]->type != ast_and
		&& lexical_table[counter]->type != ast_or
		&& lexical_table[counter]->type != ast_pipe)
	{
		if (lexical_table[counter]->type == ast_heredoc
			|| lexical_table[counter]->type == ast_redirect_out
			|| lexical_table[counter]->type == ast_redirect_in)
		{
			head = process_redirection(lexical_table, counter, subshell);
			printf("head->type = %d\n", head->type);
			i++;
			break ;
		}
		counter++;
	}
	if (i == 0)
		return (subshell);
	else
		return (head);
}

t_ast	*setting_subshell(t_ast **lexical_table, int counter)
{
	t_ast	*subshell;

	subshell = lexical_table[counter];
	trim_subshell_reparsethis(subshell);
	printf("counter = %d\n", counter);
	if (subshell->u_data.subshell.reparsethis[0] == '\0')
		return (NULL);
	subshell->u_data.subshell.child = \
	parsinginit(subshell->u_data.subshell.reparsethis);
	return (check_and_set_redirection(lexical_table, counter, subshell));
}
