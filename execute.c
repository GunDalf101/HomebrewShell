#include <readline/readline.h>
#include <readline/history.h>
#include <sys/wait.h>
#include "ast.h"

int execute_commands(t_ast* node) {
    if (!node) {
        return 0;
    }

    int status = 0;

    if (node->type == ast_cmd) {
        pid_t pid = fork();
        if (pid == -1) {
            perror("fork");
            exit(1);
        } else if (pid == 0) {           
            execvp(node->u_data.cmd.cmd, node->u_data.cmd.args);
            perror(node->u_data.cmd.cmd);
            exit(1);
        } else {
            waitpid(pid, &status, 0);
        }
    } else if (node->type == ast_pipe) {
        int pipefd[2];
        if (pipe(pipefd) == -1) {
            perror("pipe");
            exit(1);
        }

        pid_t left_pid = fork();
        if (left_pid == -1) {
            perror("fork");
            exit(1);
        } else if (left_pid == 0) {
            close(pipefd[0]);
            dup2(pipefd[1], STDOUT_FILENO);
            execute_commands(node->u_data.operation.left);
            exit(0);
        } else {
            pid_t right_pid = fork();
            if (right_pid == -1) {
                perror("fork");
                exit(1);
            } else if (right_pid == 0) {
                close(pipefd[1]);
                dup2(pipefd[0], STDIN_FILENO);
                execute_commands(node->u_data.operation.right);
                exit(0);
            } else {
                close(pipefd[0]);
                close(pipefd[1]);
                waitpid(left_pid, NULL, 0);
                waitpid(right_pid, &status, 0);
            }
        }
    } else if (node->type == ast_redirect) {
        int open_flags = (node->u_data.redirect.fd == STDOUT_FILENO) ? O_WRONLY | O_CREAT | O_TRUNC : O_RDONLY;
        int file_flags = (node->u_data.redirect.fd == STDOUT_FILENO) ? S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP : S_IRUSR | S_IRGRP | S_IROTH;
        int file_fd = open(node->u_data.redirect.path, open_flags, file_flags);
        if (file_fd == -1) {
            perror(node->u_data.redirect.path);
            exit(1);
        }
        dup2(file_fd, node->u_data.redirect.fd);
        close(file_fd);

        status = execute_commands(node->u_data.redirect.child);
    } 
	else if (node->type == ast_heredoc) {
    int pipefd[2];
    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(1);
    }

    pid_t pid = fork();

    if (pid == -1) {
        perror("fork");
        exit(1);
    } else if (pid == 0) {
        close(pipefd[0]);
        char *buffer;
        ssize_t read_result;
        while (1) {
			write(0,"heredoc>",9);
            buffer = readline("");
            if (buffer == NULL) {
                exit(1);
            }
            if (strncmp(buffer, node->u_data.heredoc.delimiter, strlen(node->u_data.heredoc.delimiter)) == 0 && strlen(node->u_data.heredoc.delimiter) == strlen(buffer)) {
                free(buffer);
                break;
            }
            read_result = write(pipefd[1], buffer, strlen(buffer));
            if (read_result == -1) {
                perror("write");
                exit(1);
            }
            read_result = write(pipefd[1], "\n", 1);
            if (read_result == -1) {
                perror("write");
                exit(1);
            }
            free(buffer);
        }
        close(pipefd[1]);
        exit(0);
    } else {
        close(pipefd[1]);

        dup2(pipefd[0], STDIN_FILENO);
        execute_commands(node->u_data.heredoc.child);
        close(pipefd[0]);

        waitpid(pid, &status, 0);
    }
}
else if (node->type == ast_subshell) {
        int pipefd[2];
        if (pipe(pipefd) == -1) {
            perror("pipe");
            exit(1);
        }

        pid_t pid = fork();

        if (pid == -1) {
            perror("fork");
            exit(1);
        } else if (pid == 0) {
            close(pipefd[0]);
            dup2(pipefd[1], STDIN_FILENO);
           // close(pipefd[1]);
            int subshell_status = execute_commands(node->u_data.subshell.child);
            write(pipefd[1], &subshell_status, sizeof(int));
            exit(0);
        } else {
            close(pipefd[1]);
            int subshell_status;
            waitpid(pid, &subshell_status, 0);
            int subshell_exit_status;
            ssize_t read_result = read(pipefd[0], &subshell_exit_status, sizeof(int));
            if (read_result == -1) {
                perror("read");
                exit(1);
            }
            status = subshell_exit_status;
            close(pipefd[0]);
        }
    }
	else if (node->type == ast_and) {
        int left_status = execute_commands(node->u_data.operation.left);
        if (left_status == 0) {
            status = execute_commands(node->u_data.operation.right);
        } else {
            status = left_status;
        } }
	else if (node->type == ast_or) {
        int left_status = execute_commands(node->u_data.operation.left);
        if (left_status != 0) {
            status = execute_commands(node->u_data.operation.right);
        } }
	else {
        printf("UNKNOWN NODE TYPE\n");
        exit(1);
    }

    return status;
}


int main() {
    char* command1_args[] = {"ls", NULL};
    t_ast* command1 = add_new_cmd("ls", command1_args, 2);

    char* command2_args[] = {"grep", "foo", NULL};
    t_ast* command2 = add_new_cmd("grep", command2_args, 2);

    t_ast* pipe1 = add_new_operation(ast_pipe, command1, command2);

    t_ast* subshell1 = add_new_subshell(pipe1);

    char* command3_args[] = {"wc", "-l", NULL};
    t_ast* command3 = add_new_cmd("wc", command3_args, 2);
	t_ast* herdoc = add_new_heredoc("dsf",command3);

    t_ast* pipe2 = add_new_operation(ast_pipe, command2, herdoc);

    char* command4_args[] = {"sort", NULL};
   t_ast* command4 = add_new_cmd("sort", command4_args, 1);

    t_ast* sort_output = add_new_redirect(1, "output.txt", command4,1);

    t_ast* pipe3 = add_new_operation(ast_pipe, herdoc, sort_output);
	
    execute_commands(pipe3);

    return 0;
}