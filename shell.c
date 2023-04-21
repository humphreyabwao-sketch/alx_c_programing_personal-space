#include "shell.h"

int main(int argc, char **argv)
{
initialize_shell();
while (true) {
display_shell_prompt();
char *input = read_user_input();
char **tokens = parse_user_input(input);
int exit_status = execute_command(tokens);
free(input);
free(tokens);
if (exit_status == 1) {
break;
}
}
return 0;
}

void initialize_shell(void)
{
printf("Initializing shell...\n");
}

void display_shell_prompt(void)
{
printf("$ ");
}

char *read_user_input(void)
{
char *input = NULL;
ssize_t buffer_size = 0;
getline(&input, &buffer_size, stdin);
return input;
}

char **parse_user_input(char *input)
{
int buffer_size = TOKEN_BUFFER_SIZE;
int position = 0;
char **tokens = malloc(buffer_size * sizeof(char*));
if (!tokens) {
fprintf(stderr, "Allocation error\n");
exit(EXIT_FAILURE);
}
char *token = strtok(input, TOKEN_DELIMITERS);
while (token) {
tokens[position] = token;
position++;
if (position >= buffer_size) {
buffer_size += TOKEN_BUFFER_SIZE;
tokens = realloc(tokens, buffer_size * sizeof(char*));
if (!tokens) {
fprintf(stderr, "Allocation error\n");
exit(EXIT_FAILURE);
}
}
token = strtok(NULL, TOKEN_DELIMITERS);
}
tokens[position] = NULL;
return tokens;
}

int execute_command(char **tokens)
{
if (tokens[0] == NULL) {
return 0;
}
for (int i = 0; i < num_builtins(); i++) {
if (strcmp(tokens[0], builtin_str[i]) == 0) {
return (*builtin_func[i])(tokens);
}
}
return launch_process(tokens);
}

int launch_process(char **args)
{
pid_t pid, wpid;
int status;

pid = fork();
if (pid == 0) {
if (execvp(args[0], args) == -1) {
perror("shell");
}
exit(EXIT_FAILURE);
} else if (pid < 0) {
perror("shell");
} else {
do {
wpid = waitpid(pid, &status, WUNTRACED);
} while (!WIFEXITED(status) && !WIFSIGNALED(status));
}

return 0;
}
