#include "shell.h"

/**
 * get_process_id - Retrieves the string representation of the current
 * process ID.
 *
 * Return: A pointer to a string representing the process ID.
 */

char *get_process_id()
{
	char *ppid_s;
	pid_t pid = getpid();

	ppid_s = number_to_character(pid);

	return (ppid_s);
}

/**
 * get_status - Retrieves the string representation of a status value.
 *
 * @n: The status value to convert to a string.
 *
 * Return: A pointer to a string representing the status value.
 */
char *get_status(int n)
{
	char *status;

	status = number_to_character(n);

	return (status);
}

/**
 * handle_comments - Removes comments from the input string.
 * @input: The input string.
 * Return : Nothing.
 */
void handle_comments(char *input)
{
	int i = 0;
	char current_char;
	int quote = 0;

	for (i = 0; input[i] != '\0'; i++)
	{
		current_char = input[i];

		if (current_char == '"')
		{
			quote = !quote;
		}
		if (current_char == '#' && !quote)
		{
			input[i] = '\0';
			break;
		}

	}

}
