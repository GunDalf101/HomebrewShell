/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_lister.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlektaib <mlektaib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 04:42:12 by mbennani          #+#    #+#             */
/*   Updated: 2023/06/24 00:23:31 by mlektaib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing101.h"
#include "ast.h"

t_ast	*find_last_node(t_ast **lst)
{
	t_ast	*last;
	t_ast	*realast;

	last = *lst;
	while (last != NULL)
	{
		realast = last;
		if (last->type == ast_heredoc)
			last = last->u_data.heredoc.next;
		else if (last->type == ast_redirect_in)
			last = last->u_data.redirect_in.next;
		else if (last->type == ast_redirect_out)
			last = last->u_data.redirect_out.next;
	}
	return (realast);
}

void	ft_redir_back(t_ast **lst, t_ast *new)
{
	t_ast	*last;
	t_ast	*tmp;

	last = *lst;
	tmp = new;
	if (*lst == NULL)
		*lst = new;
	else
	{
		tmp = find_last_node(lst);
		if (tmp->type == ast_heredoc)
			tmp->u_data.heredoc.next = new;
		else if (tmp->type == ast_redirect_in)
			tmp->u_data.redirect_in.next = new;
		else if (tmp->type == ast_redirect_out)
			tmp->u_data.redirect_out.next = new;
	}
}

t_ast	*setting_redirection(t_ast **lexical_table, int counter)
{
	t_ast	*head;
	t_ast	*node;
	int		i;

	i = counter;
	head = NULL;
	while (lexical_table[counter]
		&& (lexical_table[counter]->type == ast_heredoc
			|| lexical_table[counter]->type == ast_redirect_out
			|| lexical_table[counter]->type == ast_redirect_in))
	{
		node = lexical_table[counter];
		ft_redir_back(&head, node);
		counter++;
	}
	return (head);
}
