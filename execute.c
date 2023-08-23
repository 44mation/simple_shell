#include "shell.h"

/**
 * command_executer - Executes commands given by user.
 * @path: The path of the command to execute.
 * @av: An array of strings containing the command and its arguments.
 * @env: An array of strings representing the environment variables.
 * @status: A pointer to an integer variable to set the status.
 * Returns: Nothing.
 */
void command_executer(char *path, char **av, char **env, int *status)
{
	pid_t parent_id;

	parent_id = fork();
	if (parent_id < 0)
	{
		perror("fork has failed");
		exit(EXIT_FAILURE);
	}
	if (parent_id == 0)
	{
		execve(path, av, env);
		perror("execve has failed");
		exit(EXIT_FAILURE);
	}
	else if (parent_id > 0)
	{
		waitpid(parent_id, status, WUNTRACED);
		*status  = WEXITSTATUS(*status);
	}
}
