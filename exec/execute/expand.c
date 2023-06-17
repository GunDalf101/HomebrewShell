#include "execute.h"
char    *heredoc_expansion(char *str,t_env *env)
{
    int i = 0;
    int start = 0;
    int end = 0;
    int len = strlen(str);
    while(str[i])
    {
        if(str[i] == '$')
            {
                start = i;
                while (str[i] && str[i] != ' ' && str[i] != '\0' && str[i] != '\"' && str[i] != '\'')
                    i++;
                end = i;
                if (end - start > 1)
                {
                    char *var = ft_substr(str, start + 1, end - start - 1);
                    char *value = NULL;
                    if (get_env(env, var))
                        value = ft_strdup(get_env(env, var)->value);
                    else
                        value = ft_strdup("");
                    if (value)
                    {
                        char *firstpart = ft_substr(str, 0, start);
                        char *secondpart = ft_substr(str, end, len - end);
                        char *new_str = ft_strjoin(firstpart, value);
                        new_str = ft_strjoin(new_str, secondpart);
                        free(str);
                        str = new_str;
                        len = strlen(str);
                        i = start + strlen(value);
                    }
                    free(var);
                    free(value);
                }
            }
            i++;
    }
    return (str);
}

char	*quotes_remover(char *str) {
    int len = strlen(str);
    int i;
	int j;
    int inside_single = FALSE;
	int	inside_double = FALSE;

    for (i = j = 0; i < len; i++) {
        if (str[i] == '\'' && !inside_double) {
            inside_single = !inside_single;
        } else if (str[i] == '"' && !inside_single) {
            inside_double = !inside_double;
        } else {
            str[j++] = str[i];
        }
    }

    str[j] = '\0';
	return (str);
}



char	*quotes_busters(char *str,t_env *env) {
    int len = strlen(str);
    int i;
	int j;
    int start = 0;
    int end = 0;
    int inside_single = FALSE;
	int	inside_double = FALSE;

    for (i = j = 0; i < len; i++) {
       
        if (str[i] == '\'' && !inside_double) {
            inside_single = !inside_single;
        } else if (str[i] == '"' && !inside_single) {
            inside_double = !inside_double;
        } 
        if (!inside_single)
        {
          if(str[i] == '$')
            {
                start = i;
                while (str[i] && str[i] != ' ' && str[i] != '\0' && str[i] != '\"' && str[i] != '\'')
                    i++;
                end = i;
                if (end - start > 1)
                {
                    char *var = ft_substr(str, start + 1, end - start - 1);
                    char *value = NULL;
                    if (get_env(env, var))
                        value = ft_strdup(get_env(env, var)->value);
                    else
                        value = ft_strdup("");
                    if (value)
                    {
                        char *firstpart = ft_substr(str, 0, start);
                        char *secondpart = ft_substr(str, end, len - end);
                        char *new_str = ft_strjoin(firstpart, value);
                        new_str = ft_strjoin(new_str, secondpart);
                        free(str);
                        str = new_str;
                        len = strlen(str);
                        i = start + strlen(value);
                        j = i;
                    }
                    free(var);
                    free(value);
                }
            }
        }
        if(str[i] && (str[i] != '\'' || inside_double || str[i] != '"' || inside_single))
            str[j++] = str[i];
    }

    str[j] = '\0';
	return (quotes_remover(str));
}


void expand(t_ast *node,t_env **env)
{
    (void)env;
    if(node->type == ast_cmd)
    {
        int i = 0;
        node->u_data.cmd.cmd = quotes_busters(node->u_data.cmd.cmd,*env);
        while(node->u_data.cmd.args[i])
        {
            node->u_data.cmd.args[i] = quotes_busters(node->u_data.cmd.args[i],*env);
            i++;
        }
    }
}