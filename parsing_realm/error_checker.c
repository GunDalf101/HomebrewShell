/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbennani <mbennani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 23:10:09 by mbennani          #+#    #+#             */
/*   Updated: 2023/06/18 01:46:51 by mbennani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "parsing101.h"

void	error_thrower(int code)
{
	if (code == 0)
		printf("Error: close whatever you opened\n");
}