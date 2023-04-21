#ifndef SHELL_H
#define SHELL_H

/* Libraries */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>

/* Function prototypes */
void initialize_shell(void);
void display_shell_prompt(void);
char *read_user_input(void);
char **parse_user_input(char *input);
int execute_command(char **tokens);
int launch_process(char **args);
int shell_cd(char **args);
int shell_help(char **args);
int shell_exit(char **args);
int num_builtins(void);

/* Global variables */
char *builtin_str[];
int (builtin_func[]) (char *) = {&shell_cd, &shell_help, &shell_exit};

#endif /* SHELL_H */
