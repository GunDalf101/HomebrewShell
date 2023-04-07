#include "commands.h"

int check_key(char *key)
{
	if(!ft_isalpha(key[0]) && key[0] != '_')
		return 0;
	return 1;
}

int envcmd(t_env *head)
{
	while(head)
	{
		ft_putstr_fd(head->key,1);
		ft_putstr_fd("=",1);
		ft_putstr_fd(head->value,1);
		ft_putstr_fd("\n",1);
		head = head->next;
	}
	return 0;
}



int envadd(t_env **head,t_ast *node)
{
	int k = 0;
	t_env *tmp;
	t_env *new = key_value_to_list(node->u_data.cmd.args+1);
	envcmd(*head);
	while (new)
	{
		if (check_key(new->key))
		{
			tmp = get_env(*head,new->key);
			if(!tmp)
				envadd_back(head, new);
			else
				tmp->value = new->value;
		}
		else
		{
			ft_putstr_fd(new->key,1);
			ft_putstr_fd("=",1);
			ft_putendl_fd(new->value,1);
			k = 1;
		}
		new = new->next;
	}
	return k;
}


