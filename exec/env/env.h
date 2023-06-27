/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlektaib <mlektaib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 21:21:07 by mlektaib          #+#    #+#             */
/*   Updated: 2023/06/24 23:26:21 by mlektaib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H
# include "../../libft/libft.h"

typedef struct s_env
{
	char			*key;
	char			*value;
	int				hidden;
	int				rank;
	int				append;
	struct s_env	*next;
}					t_env;

typedef struct s_lstenv
{
	size_t			size;
	char			**envs;
	int				i;
	char			*env;
	char			*tmp;
}					t_lstenv;

typedef struct s_argtoenv
{
	t_env			*head;
	char			**keyvalue;
	int				d;
	int				k;
	int				i;
	int				i2;
	char			*key;
	char			*value;
	int				found;
}					t_argtoenv;

typedef struct s_loadenv
{
	t_env	*head;
	char	*key;
	char	*value;
	int		i;
	char	*tmp;
	int		found;
}				t_loadenv;

void				envadd_back(t_env **head, t_env *node, int hidden);
t_env				*envnew(char *key, char *value, int append);
t_env				*load_env(char **env);
t_env				*get_env(t_env *head, char *env);
t_env				*key_value_to_list(char **env);
char				**lst_to_env(t_env *head);
int					lstsize(t_env *head);
void				free_env_lst(t_env *head);
void				new_clearenv(t_env **head);
void				key_value_helper(t_argtoenv *var, char *env);
void				argtoenv_init(t_argtoenv *var);
void				load_env_init(t_loadenv *var);
void				load_helper(t_loadenv *var, char **env);
#endif