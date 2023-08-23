#include "shell.h"

/**
 * check_access - checks the access.
 * of a given command in the command line.
 * @current: current path turned into linked lists.
 * @command:  line from user entered by getline and path list.
 * Return: full path of the command
*/

char *check_access(char *command, list_paths *current)
{
	char *full_path;
	int found_path, length, command_length, current_path_legnth;

	if (current == NULL)
		return (NULL);
	while (current)
	{
		current_path_legnth = _strlen(current->path);
		command_length = _strlen(command);
		length = (current_path_legnth + command_length + 2);

		full_path = (char *)malloc(length * sizeof(char));
		_strcpy(full_path, current->path);
		_strcat(full_path, "/");
		_strcat(full_path, command);
		found_path = 0;
		if (access(full_path, X_OK) == 0)
		{
			found_path = 1;
			break;
		}
		else
			free(full_path);
		current = current->next;
	}
	if (found_path)
		return (full_path);

	else
		return (NULL);
}
/**
* check_input_file - checks if a file exists and is readable.
* @file: name of file to check
*Return: pointer to @file if it exists
*/
char *check_input_file(char *file)
{
char *command;
command = _strdup(file);

	return (command);
}

/**
 * check_mode - a function that checks the mode of my terminal
 * @argc: arguments' count
 * Return: 1 in case of interactive mode,
 *			0 in case of non-interactive mode,
 *			-1 in case of error.
*/
int check_mode(int argc)
{
	struct stat stdin_stat;

	fstat(STDIN_FILENO, &stdin_stat);
	if (argc == 1 && isatty(STDIN_FILENO))
		return (INTERACTIVE_MODE);
	if ((!isatty(STDIN_FILENO) && argc == 1))
		return (NON_INTERACTIVE_PIPE);
	if ((argc >= 1))
		return (NON_INTERACTIVE_MODE);
	return (ERROR);
}
