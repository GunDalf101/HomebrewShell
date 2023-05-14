/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlektaib <mlektaib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 18:35:41 by mlektaib          #+#    #+#             */
/*   Updated: 2023/04/29 14:16:39 by mlektaib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	make_remain(t_gnl **buffer)
{
	t_gnl	*last;
	t_gnl	*remain_node;
	int		i;
	int		j;

	remain_node = malloc(sizeof(t_gnl));
	if (buffer == NULL || remain_node == NULL)
		return ;
	remain_node->next = NULL;
	last = ft_gnllast(*buffer);
	i = 0;
	while (last->content[i] && last->content[i] != '\n')
		i++;
	if (last->content && last->content[i] == '\n')
		i++;
	remain_node->content = malloc(((ft_strlen(last->content) - i) + 1));
	if (remain_node->content == NULL)
		return ;
	j = 0;
	while (last->content[i])
		remain_node->content[j++] = last->content[i++];
	remain_node->content[j] = '\0';
	ft_gnlclear(buffer);
	*buffer = remain_node;
}

t_gnl	*ft_gnllast(t_gnl *gnl)
{
	t_gnl	*last;

	last = gnl;
	if (!last)
		return (0);
	while (last->next)
	{
		last = last->next;
	}
	return (last);
}

void	ft_gnlclear(t_gnl **gnl)
{
	t_gnl	*temp;

	if (!gnl || !*gnl)
		return ;
	if (gnl)
	{
		while (*gnl)
		{
			temp = (*gnl)->next;
			free((*gnl)->content);
			free(*gnl);
			*gnl = temp;
		}
	}
	*gnl = NULL;
}

int	ft_check(t_gnl *buffer)
{
	t_gnl	*last;
	size_t	i;

	i = 0;
	if (!buffer)
		return (0);
	last = ft_gnllast(buffer);
	while (last->content[i])
	{	
		if (last->content[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

size_t	ft_strlen(const char *str)
{
	size_t	count;

	count = 0;
	while (str[count])
		count++;
	return (count);
}