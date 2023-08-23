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
 * Return: pointer to @file if it exists
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
 * Return: 1 or 0 or -1
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

/**
 * _setenv - Set environment variable
 * @key: The name of the environment variable
 * @value: The value to be assigned to the environment variable
 * @current: Pointer to the list_paths structure
 */

void _setenv(char *key, char *value, list_paths *current)
{
	int count = 0;
	char *full_env = NULL;

	if (key == NULL || value == NULL)
	{
		return;
	}
	if (current == NULL)
	{
		return;
	}
	count = _strlen(key) + _strlen(value) + 2;
	full_env = malloc(count);
	if (full_env == NULL)
	{
		return;
	}
	_strcpy(full_env, key);
	_strcat(full_env, "=");
	_strcat(full_env, value);
	full_env[count - 1] = '\0';
	free(full_env);

}
/**
 * _cd - Change the current working directory.
 * @command_array: array of strings of commands.
 * @argument_vector:argv
 * Return: None.
*/
int _cd(char **command_array, char **argument_vector)
{

	char *directory = command_array[1];
	char cwd[1024];

	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		perror("error in getcwd()");
		return (1);
	}
	if (directory == NULL || _strcmp(directory, "~") == 0)
		directory = _getenv("HOME");
	else if (_strcmp(directory, "-") == 0)
		directory = _getenv("OLDPWD");
	if (chdir(directory) == -1)
	{
		write(STDERR_FILENO, argument_vector[0], _strlen(argument_vector[0]));
		write(STDERR_FILENO, ": 1", 3);
		write(STDERR_FILENO, ": ", 2);
		write(STDERR_FILENO, command_array[0], _strlen(command_array[0]));
		write(STDERR_FILENO, ": can't cd to ", 14);
		write(STDERR_FILENO, command_array[1], _strlen(command_array[1]));
		write(STDERR_FILENO, "\n", 1);
		return (1);
	}
	else
	{
		setenv("OLDPWD", cwd, 1);
		if (getcwd(cwd, sizeof(cwd)) == NULL)
		{
			perror("error in getcwd()");
			return (1);
		}
	}
	return (0);
}
