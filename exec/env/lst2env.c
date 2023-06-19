/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst2env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlektaib <mlektaib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 21:21:04 by mlektaib          #+#    #+#             */
/*   Updated: 2023/04/10 01:42:02 by mlektaib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

char	*append_env_mode(char *key, int *k)
{
	char	*correctkey;
	int		keylen;

	keylen = ft_strlen(key);
	correctkey = malloc(keylen - 1);
	ft_memmove(correctkey, key, keylen);
	correctkey[keylen - 1] = 0;
	*k = 1;
	free(key);
	return (correctkey);
}

void	free_env_lst(t_env *head)
{
	t_env	*temp;

	if (head)
	{
		while (head)
		{
			temp = head->next;
			free(head->key);
			free(head->value);
			free(head);
			head = temp;
		}
	}
}

char	**lst_to_env(t_env *head)
{
	size_t	size;
	char	**envs;
	int		i;
	char	*env;
	char	*tmp;

	size = lstsize(head);
	envs = malloc(size * sizeof(char *) + 1);
	i = 0;
	while (head != NULL)
	{
		if(head->hidden == 0)
		{
			tmp = ft_strdup(head->key);
			if(head->value != NULL)
			{
				tmp = ft_strjoin(head->key, "=");
				env = ft_strjoin(tmp, head->value);
			}
			else
				env = ft_strdup(tmp);
			free(tmp);
			envs[i] = env;
			i++;
		}
		head = head->next;
	}
	envs[i] = NULL;
	return (envs);
}

int	lstsize(t_env *head)
{
	t_env	*tmp;
	int		i;

	i = 0;
	tmp = head;
	while (tmp)
	{
		if(tmp->hidden == 0)
			i++;
		tmp = tmp->next;
	}
	return (i);
}
