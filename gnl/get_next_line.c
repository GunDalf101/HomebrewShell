/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlektaib <mlektaib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 18:34:16 by mlektaib          #+#    #+#             */
/*   Updated: 2023/04/11 00:42:14 by mlektaib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static t_gnl	*buffer;
	int				readed;
	char			*line;
	int				n;

	readed = 1;
	n = 0;
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &line, 0) < 0)
		return (0);
	n = read_file(fd, &readed, &buffer);
	line = extract_line(buffer);
	if (line && n != 0)
		make_remain(&buffer);
	if (n == 0)
		ft_gnlclear(&buffer);
	return (line);
}

int	read_file(int fd, int *readed, t_gnl **buffer)
{
	char	*content;
	int		end;

	end = 1;
	while (ft_check(*buffer) != 1 && *readed > 0)
	{
		content = malloc((BUFFER_SIZE + 1) * sizeof(char));
		if (!content)
			return (0);
		*readed = (int)read(fd, content, BUFFER_SIZE);
		if (*readed <= 0)
		{
			free(content);
			end = 0;
			break ;
		}
		add_tolist(content, buffer, *readed);
		free(content);
	}
	return (end);
}

void	add_tolist(char *content, t_gnl **buffer, int readed)
{
	t_gnl	*newnode;
	int		i;
	t_gnl	*last;

	i = 0;
	if (!content || read <= 0 || !buffer)
		return ;
	newnode = malloc(sizeof(t_gnl));
	if (!newnode)
		return ;
	newnode->content = malloc(sizeof(char) * (readed + 1));
	if (!newnode->content)
		return ;
	while (i < readed)
	{
		newnode->content[i] = content[i];
		i++;
	}
	newnode->content[i] = 0;
	newnode->next = NULL;
	last = ft_gnllast(*buffer);
	if (!last)
		*buffer = newnode;
	else
		last->next = newnode;
}

char	*extract_line(t_gnl *buffer)
{
	char	*line;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!buffer)
		return (0);
	allocline(buffer, &line);
	if (!line)
		return (0);
	while (buffer)
	{
		j = 0;
		while (buffer->content[j] != '\n' && buffer->content[j])
					line[i++] = buffer->content[j++];
		if (buffer->content[j] == '\n')
			line[i++] = '\n';
		buffer = buffer->next;
	}
	line[i] = 0;
	return (line);
}

void	allocline(t_gnl *buffer, char **line)
{
	size_t	count;
	size_t	i;
	int		nl;

	count = 0;
	i = 0;
	nl = 0;
	if (!buffer)
		return ;
	while (buffer)
	{
		i = 0;
		while (buffer->content[i] != '\n' && buffer->content[i++])
				count++;
		if (buffer->content[i] == '\n')
			nl = 1;
		buffer = buffer->next;
	}
	if (count == 0 && nl != 1)
	{
		*line = 0;
		return ;
	}
	count++;
	*line = malloc(sizeof(char) * count +1);
}
