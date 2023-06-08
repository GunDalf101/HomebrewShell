/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbennani <mbennani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 21:21:07 by mlektaib          #+#    #+#             */
/*   Updated: 2023/06/08 16:25:06 by mbennani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H
# include "../../libft/libft.h"

typedef struct s_env
{
	char			*key;
	char			*value;
	int 			hidden;
	int				rank;
	int				append;
	struct s_env	*next;
}					t_env;

void	envadd_back(t_env **head, t_env *node,int hidden);
t_env				*envnew(char *key, char *value, int append);
t_env				*load_env(char **env);
t_env				*get_env(t_env *head, char *env);
t_env				*key_value_to_list(char **env);
char				**lst_to_env(t_env *head);
int					lstsize(t_env *head);
void				free_env_lst(t_env *head);
char				*append_env_mode(char *key, int *k);
// void				clearenv(t_env **head);

#endif