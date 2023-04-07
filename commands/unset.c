#include "commands.h"

void freeenvnode(t_env *tmp)
{
	free(tmp->key);
	free(tmp->value);
	free(tmp);
}
int	unsetcmd(t_env **head,t_ast *node)
{
	int k = 0;
	t_env *tmp;
	t_env *prev;
	if(!node->u_data.cmd.args[1])
		exportcmd(*head);
	t_env *deleted = key_value_to_list(node->u_data.cmd.args+1);

	while (deleted)
	{
		prev = NULL;
		tmp = *head;
		while (tmp)
		{
			if (strcmp(tmp->key, deleted->key) == 0)
			{
				if (prev == NULL)
					*head = tmp->next;
				else
				{
					prev->next = tmp->next;
				}
				freeenvnode(tmp);
				break ;
			}
			prev = tmp;
			tmp = tmp->next;
		}
		deleted = deleted->next;
	}
	return (0);
}