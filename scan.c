#include"shell.h"
/**
 * scan_cmd_user - Scans and retrieves user input command.
 *
 * @current: A pointer to a list_paths struct representing the current path.
 *
 * Return: command after scanning.
 */
char *scan_cmd_user(list_paths *current)
{
	ssize_t read;
	size_t s = 0;
	char *command = NULL;
	/*prompt ($) and getting the input from the user*/
	write(STDOUT_FILENO, "($) ", 4);
	read = getline(&command, &s, stdin);
	/*dealing with end of file or ctrl + D*/
	if (read == EOF)
	{
		/*write new line and free*/
		write(STDOUT_FILENO, "\n", 1);
		free_list(current);
		free(command);
		exit(0);
	}
	/* If the user enters a blank line, return NULL */
	if (read == 1 && command[0] == '\n')
	{
		free(command);
		return (NULL);
	}

	command[read - 1] = '\0';

	return (command);
}
/**
 * scan_command_files - Scans command files based on the operation mode.
 * @op_mode: The operation mode.
 * @file_name: The name of the command file.
 * @shell_name: The name of the shell program.
 * Return: The array of command lines read from the file.
 */
char **scan_command_files(int op_mode, char *file_name, char *shell_name)
{
	char **command_lines;

	if (op_mode == NON_INTERACTIVE_PIPE)
	{
		command_lines = noninteractive_pipes_handler();
		if (!command_lines)
			exit(0);
	}
	else if (op_mode == NON_INTERACTIVE_MODE)
	{
		command_lines = noninteractive_files_handler(file_name, shell_name);
		if (!command_lines)
			exit(0);
	}
	return (command_lines);
}
