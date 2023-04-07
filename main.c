
#include "minishell.h"


int	main(int argc, char *argv[], char **env)
{
	t_env *envlst = load_env(env);
	t_env *tmp;
	char *command1_args[] = {"export", "test+=te1st1",NULL};
	t_ast *command1 = add_new_cmd("export", command1_args, 2,ast_imp);
	char *command2_args[] = {"unset", "test+=tesghjht1",NULL};
	t_ast *command2 = add_new_cmd("unset", command2_args, 2,ast_imp);
	char *command3_args[] = {"export",NULL};
	t_ast *command3 = add_new_cmd("export", command3_args, 1,ast_imp);
	//exportcmd(envlst);
	//exportcmd(envlst);
	//exportcmd(envlst);
	
	
// 	while(1){
// 		readline("");

// 	char *command2_args[] = {"ls", "-la", NULL};
// 	t_ast *command2 = add_new_cmd("ls", command2_args, 2,ast_cmd);


// 	t_ast *pipe1 = add_new_operation(ast_pipe, command2, command1);
// 	t_ast *root = pipe1;
	
// 	// if(root->type == ast_exit)
// 	// {
// 	// 	exit(atoi(root->u_data.cmd.args[1]));
// 	// }
execute_commands(command1,&envlst);
execute_commands(command1,&envlst);
execute_commands(command3,&envlst);
 execute_commands(command2,&envlst);
//// printf("sda\n");
//execute_commands(command3,&envlst);
// 	printf("main exit %d \n",k);
// }
// 	exit (k);
}