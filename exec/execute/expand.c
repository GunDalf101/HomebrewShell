#include "execute.h"
extern t_global g_global;


void expand_intialize(t_expand *expand,char *str)
{
    expand->str = str;
    expand->i = 0;
    expand->j = 0;
    expand->len = strlen(str);
    expand->inside_single = FALSE;
    expand->inside_double = FALSE;
    expand->start = 0;
    expand->end = 0;
    expand->value = NULL;
    expand->var = NULL;
}

void expand_start(t_expand *expand,t_env *env)
{
    expand->start = expand->i;
    expand->i++;
    while (expand->str[expand->i] && (ft_isalnum(expand->str[expand->i]) || expand->str[expand->i] == '_'))
        expand->i++;
    if (expand->str[expand->i] == '?')
        expand->i++;
    expand->end = expand->i;
    if (expand->end - expand->start > 1)
    {
        expand->var = ft_substr(expand->str, expand->start + 1, expand->end - expand->start - 1);
        expand->value = NULL;
        if(expand->var[0] == '?')
            expand->value = ft_itoa(g_global.exit_status);
        else if(get_env(env, expand->var))
            expand->value = ft_strdup(get_env(env, expand->var)->value);
        else
            expand->value = NULL;
        if (expand->value)
            replace_env(expand);
        free(expand->var);
        free(expand->value);
    }
}

char	*quotes_busters(char *str,t_env *env) {
    t_expand expand;

    expand_intialize(&expand, str);
    while(expand.i < expand.len)
    {
       
        if (expand.str[expand.i] == '\'' && !expand.inside_double)
            expand.inside_single = !expand.inside_single;
        else if (expand.str[expand.i] == '"' && !expand.inside_single)
            expand.inside_double = !expand.inside_double;
        if (!expand.inside_single)
          if(expand.str[expand.i] == '$')
            expand_start(&expand,env);
        if(expand.str[expand.i] && (expand.str[expand.i] != '\'' || expand.inside_double || expand.str[expand.i] != '"' || expand.inside_single))
            expand.str[expand.j++] = expand.str[expand.i];
        expand.i++;
    }
    expand.len = ft_strlen(expand.str);
    expand.str = quotes_remover(expand.str);
    if (expand.len == 0)
        return (NULL);
    str[expand.j] = '\0';
	return (expand.str);
}

void shift_args(t_ast *node,int i)
{
    while(node->u_data.cmd.args[i+1])
    {
        node->u_data.cmd.args[i] = node->u_data.cmd.args[i+1];
        i++;
    }
}

t_ast *expand(t_ast *node,t_env **env)
{
    (void)env;
    if(node->type == ast_cmd || node->type == ast_imp)
    {
        int i = 0;
        node->u_data.cmd.cmd = quotes_busters(node->u_data.cmd.cmd,*env);
        while(node->u_data.cmd.args[i])
        {
            node->u_data.cmd.args[i] = quotes_busters(node->u_data.cmd.args[i],*env);
            if(node->u_data.cmd.args[i] == NULL && node->u_data.cmd.args[i+1])
            {
                shift_args(node,i);
                i = 0;
            }
            i++;
        }
        node->u_data.cmd.cmd = node->u_data.cmd.args[0];
    }
    if(node->u_data.cmd.arg_count == 0)
        return(NULL);
    return(node);
}