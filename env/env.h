#ifndef ENV_H
# define ENV_H
# include "../libft.h"
typedef struct s_env
{
	char			*key;
	char			*value;
	int				rank;
	int				append;
	struct s_env	*next;
}					t_env;

void				envadd_back(t_env **head, t_env *node);
t_env				*envnew(char *key, char *value,int append);
t_env				*load_env(char **env);
t_env				*get_env(t_env *head, char *env);
t_env				*key_value_to_list(char **env);

#endif