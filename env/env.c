#include "env.h"
#include <string.h>


t_env	*key_value_to_list(char **env)
{
	t_env *head;
	head = NULL;
	char **keyvalue;
	int d ;
	int k = 0;
	while (*env != NULL)
	{
		keyvalue = ft_split(*env,'=');
		d = ft_strlen(keyvalue[0])-1;
		
		if(keyvalue[0][d] == '+')
		{
			keyvalue[0][d] = '\0';
			k= 1;
		}
		if(!keyvalue[1])
			envadd_back(&head,envnew(keyvalue[0],ft_strdup(""),k));
		else
			envadd_back(&head,envnew(keyvalue[0],keyvalue[1],k));
		env++;
	}
	return head;
}

t_env	*envnew(char *key, char *value,int append)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return (0);
	new->key = key;
	new->value = value;
	new->append =  append;
	new->next = NULL;
	return (new);
}

void	envadd_back(t_env **head, t_env *node)
{
	t_env	*tmp;

	if (!head)
		return ;
	tmp = *head;
	if (*head == NULL)
		*head = node;
	else
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = node;
	}
}

t_env	*load_env(char **env)
{
	t_env *head;
	head = NULL;
	char **keyvalue;
	while (*env != NULL)
	{
		keyvalue = ft_split(*env,'=');
		envadd_back(&head,envnew(keyvalue[0],keyvalue[1],0));
		env++;
	}
	return head;
}

t_env *get_env(t_env *head,char *env)
{
	t_env *tmp;
	tmp = head;
	if(!env)
		return 0;
	while(tmp)
	{
		if(strcmp(tmp->key,env) == 0)
			return(tmp);
		tmp = tmp->next;
	}
	return 0;
}