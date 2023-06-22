/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlektaib <mlektaib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 21:21:07 by mlektaib          #+#    #+#             */
/*   Updated: 2023/06/22 17:28:46 by mlektaib         ###   ########.fr       */
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

typedef struct s_lstenv
{
	size_t	size;
	char	**envs;
	int		i;
	char	*env;
	char	*tmp;
} t_lstenv;

typedef struct s_argtoenv 
{
	t_env	*head;
	char	**keyvalue;
	int		d;
	int		k;
	int		i;
}	t_argtoenv;

void	envadd_back(t_env **head, t_env *node,int hidden);
t_env	*envnew(char *key, char *value, int append);
t_env	*load_env(char **env);
t_env	*get_env(t_env *head, char *env);
t_env	*key_value_to_list(char **env);
char	**lst_to_env(t_env *head);
int		lstsize(t_env *head);
void	free_env_lst(t_env *head);
char	*append_env_mode(char *key, int *k);
void	clearenv(t_env **head);
void	key_value_helper(t_argtoenv *var,char **env);
void	argtoenv_init(t_argtoenv *var);

#endif