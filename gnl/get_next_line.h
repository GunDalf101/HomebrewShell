/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlektaib <mlektaib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 18:35:56 by mlektaib          #+#    #+#             */
/*   Updated: 2023/04/11 00:43:11 by mlektaib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

typedef struct s_gnl
{
	char			*content;
	struct s_gnl	*next;
}	t_gnl;
char	*get_next_line(int fd);
int		read_file(int fd, int *readed, t_gnl **buffer);
void	add_tolist(char *content, t_gnl **buffer, int readed);
char	*extract_line(t_gnl *buffer);
void	allocline(t_gnl *buffer, char **line);
int		ft_check(t_gnl *buffer);
size_t	ft_strlen(const char *str);
void	ft_gnlclear(t_gnl **gnl);
void	make_remain(t_gnl **head);
t_gnl	*ft_gnllast(t_gnl *gnl);

#endif
