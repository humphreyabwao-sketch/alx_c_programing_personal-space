#include "shell.h"

/**
 * cd_built-in - Changes the current working directory of the shell
 * @args: List of arguments passed to the cd command
 * Return: Always returns 1, to continue executing the shell
 */
int cd_built_in(char **args)
{
  if (args[1] == NULL)
  {
    fprintf(stderr, "Expected argument to \"cd\"\n");
  }
  else
  {
    if (chdir(args[1]) != 0)
    {
      perror("Failed to change directory");
    }
  }

  return 1;
}

/**
 * exit_built-in - Exits the shell
 * @args: List of arguments passed to the exit command
 * Return: Always returns 0, to terminate the shell
 */
int exit_built_in(char **args)
{
  return 0;
}
