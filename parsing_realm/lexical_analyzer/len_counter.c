/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   len_counter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbennani <mbennani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 02:25:27 by mbennani          #+#    #+#             */
/*   Updated: 2023/06/22 02:27:05 by mbennani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexing_lexer.h"

size_t	strtablen(char **tokens)
{
	size_t	cnt;

	cnt = 0;
	while (tokens[cnt])
		cnt++;
	return (cnt);
}

// the exact lengthof astable

size_t	size_lol(char **tokens)
{
	size_t	i;
	size_t	cnt;

	i = 0;
	cnt = 1;
	while (tokens[i])
	{
		if (tokens[i][0] == '>' || tokens[i][0] == '<')
			cnt++;
		if (tokens[i][0] == '|' || tokens[i][0] == '&')
			cnt += 2;
		if (tokens[i][0] == '(')
			cnt++;
		i++;
	}
	return (cnt + 1);
}
