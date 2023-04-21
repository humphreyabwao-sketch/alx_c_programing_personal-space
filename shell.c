#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

Function prototypes
void initialize_shell();
void display_shell_prompt();
char* read_user_input();
char** parse_user_input(char* input);
void execute_command(char** tokens);

 Initialize the shell
void initialize_shell() {
    // Perform any necessary initialization steps
    printf("Welcome to MyShell!\n");
}

 Main function
int main() {
    initialize_shell();

    while (1) {
        // Display the shell prompt and read user input
        display_shell_prompt();
        char* input = read_user_input();

        // Parse user input into tokens
        char** tokens = parse_user_input(input);

        // Execute command based on parsed tokens
        execute_command(tokens);

        // Free allocated memory
        free(input);
        free(tokens);
    }

    return 0;
}

Display the shell prompt
void display_shell_prompt() {
    printf("$ ");
}

Read user input
char* read_user_input() {
    char* input = NULL;
    ssize_t buffer_size = 0;

    // Read input from the user
    getline(&input, &buffer_size, stdin);

    // Remove newline character from input
    input[strcspn(input, "\n")] = '\0';

    return input;
}

Parse user input into tokens
char** parse_user_input(char* input) {
    int buffer_size = 64, position = 0;
    char** tokens = malloc(buffer_size * sizeof(char*));
    char* token;

    // Check if allocation was successful
    if (!tokens) {
        fprintf(stderr, "Memory allocation error\n");
        exit(EXIT_FAILURE);
    }

    // Split input into tokens
    token = strtok(input, " ");
    while (token != NULL) {
        tokens[position] = token;
        position++;

        // Increase buffer size if necessary
        if (position >= buffer_size) {
            buffer_size += 64;
            tokens = realloc(tokens, buffer_size * sizeof(char*));

            // Check if reallocation was successful
            if (!tokens) {
                fprintf(stderr, "Memory allocation error\n");
                exit(EXIT_FAILURE);
            }
        }

        token = strtok(NULL, " ");
    }
    tokens[position] = NULL;

    return tokens;
}

Execute command based on parsed tokens
void execute_command(char** tokens) {
    pid_t pid, wpid;
    int status;

    pid = fork();
    if (pid == 0) {
        // Child process
        if (execvp(tokens[0], tokens) == -1) {
            perror("MyShell");
        }
        exit(EXIT_FAILURE);
    } else if (pid < 0) {
        // Fork error
        perror("MyShell");
    } else {
        // Parent process
        do {
            wpid = waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }
}
