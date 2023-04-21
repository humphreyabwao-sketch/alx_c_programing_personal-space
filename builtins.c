#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "shell.h"

int shell_cd(char **args);
int shell_help(char **args);
int shell_exit(char **args);

char *builtin_str[] = {
"cd",
"help",
"exit"
};

int (*builtin_func[]) (char **) = {
&shell_cd,
&shell_help,
&shell_exit
};

int num_builtins() {
return sizeof(builtin_str) / sizeof(char *);
}

int shell_cd(char **args)
{
if (args[1] == NULL) {
fprintf(stderr, "shell: expected argument to \"cd\"\n");
} else {
if (chdir(args[1]) != 0) {
perror("shell");
}
}
return 1;
}

int shell_help(char **args)
{
int i;
printf("Shell\n");
printf("Type program names and arguments, and hit enter.\n");
printf("The following are built in:\n");

for (i = 0; i < num_builtins(); i++) {
printf("  %s\n", builtin_str[i]);
}

printf("Use the man command for information on other programs.\n");
return 1;
}

int shell_exit(char **args)
{
return 0;
}
