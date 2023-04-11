#include <stdio.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>

void handle_interrupt(int signal) {
    rl_clear_signals();
    printf("\nInterrupt signal received. Press Ctrl-C again to exit.\n");
}

int main() {
    // Catch the interrupt signal and call the handle_interrupt() function
    signal(SIGINT, handle_interrupt);

    char *input;
    while (1) {
        input = readline("Enter some text: ");
        if (input == NULL) {
            // Exit the program if Ctrl-D is pressed
            printf("Exiting...\n");
            break;
        }
        printf("You entered: %s\n", input);
        add_history(input);
        free(input);
    }
    return 0;
}