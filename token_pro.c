#include "shell.h"

/**
 * piped_characters_count - counts the occurrences of a character in a string
 *
 * @string: the string to search for the character
 * @c: the character to search for
 * Return: the number of occurrences of @c in @string
 */
unsigned int piped_characters_count(char *string, char c)
{
	unsigned int counter = 0;

	while (*string != '\0')
	{
		if (*string == c)
			counter++;
		string++;
	}
	return (counter + 1);
}
/**
 * print_env - Prints the environment variables.
 * @status: A pointer to an integer variable to set the status.
*/
void print_env(int *status)
{
	int i;

	/* Iterate over the environment variables until a NULL is encountered */
	for (i = 0; environ[i] != NULL; i++)
	{
		write(STDOUT_FILENO, environ[i], _strlen(environ[i]));
		write(STDOUT_FILENO, "\n", 1);
	}
	/* Set the status to indicate successful completion */
	*status = 0;
}
/**
 * print_error - Prints an error message to the standard error stream.
 * @shell_name: The name of the shell program.
 * @count: The command count.
 * @command_array: The command or argument causing the error.
 * @type_of_error: The type of error.
 * Return: nothing
 */

void print_error(char *shell_name, int count,
		char *command_array, int type_of_error)
{
	char *counter_string;

	/* Convert the command count to a string */
	counter_string = number_to_character(count);

	/* Print the shell name, command count, and colon separator */
	write(STDERR_FILENO, shell_name, _strlen(shell_name));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, counter_string, _strlen(counter_string));
	write(STDERR_FILENO, ": ", 2);

	/* Check the type of error and print the corresponding error message */
	if (type_of_error == EXIT_ERROR)
	{
		write(STDERR_FILENO, "Illegal number: ", 16);
		write(STDERR_FILENO, command_array, _strlen(command_array));
		write(STDERR_FILENO, "\n", 1);
	}
	else if (type_of_error == NOT_FOUND)
	{
		write(STDERR_FILENO, "not found\n", 10);
	}
	else if (type_of_error == PERMISSION_DENIED)
	{
		write(STDERR_FILENO, "Permission denied\n", 18);
	}

	free(counter_string);
}

/**
 * process_token - Processes a token
 * @token: The input token to process.
 * @status: integer
 * Return: allocated string
*/
char *process_token(char *token, int status)
{
	char *cmnd, *variable;

	cmnd = NULL;
	variable = NULL;

	if (_strcmp("$$", token) == 0)
		cmnd = get_process_id();
	else if (_strcmp("$?", token) == 0)
		cmnd = get_status(status);
	else if (token[0] == '$' && token[1] != '\0')
	{
		variable = _getenv(&token[1]);
		cmnd = (variable != NULL) ? _strdup(variable) : _strdup("");
	}
	else
		cmnd = _strdup(token);
	return (cmnd);
}

