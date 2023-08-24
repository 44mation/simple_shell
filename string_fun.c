#include"shell.h"

/**
 * int_to_str - Converts an integer to a string.
 * @n: The integer to convert.
 * @str: The buffer to store the resulting string.
 * Return : nothing
 */
void int_to_str(int n, char *str)
{
	int tmp;
	int i = 0;

	if (n == 0)
	{
		str[i++] = '0';
	}
	tmp = n;
	while (tmp > 0)
	{
		tmp /= 10;
		i++;
	}
	tmp = n;
	while (i > 0)
	{
		str[--i] = tmp % 10 + '0';
		tmp /= 10;
	}
	str[i] = '\0';
}
/**
 * line_count - Counts the number of lines in a given string.
 * @line: The input string.
 * Return: The number of lines in the string.
 */
int line_count(char *line)
{
	int i = 0;

	while (*line != '\0')
	{
		i++;
		line++;
	}
	return (i);
}

/**
 * line_to_vector - converts a string into an array of strings
 * @command: the string to convert
 * @status: an integer representing the status of the command
 * Return: a pointer to a char array.
 */
char **line_to_vector(char *command, int status)
{
	char *copied_line, *token, **argument_vector, *variable, *cmde;
	int i = 0, character_count;

	if (command[0] == '\0')
		return (NULL);
	copied_line = _strdup(command);
	if (copied_line == NULL)
		return (NULL);
	character_count = char_count(copied_line, ' ');
	argument_vector = malloc((character_count + 1) * sizeof(char *));
	token = _strtok(copied_line, TOK_D);
	cmde = flags_handler(token, command, argument_vector, status);
	argument_vector[i++] = cmde;
	while (token != NULL)
	{
		token = _strtok(NULL, TOK_D);
		if (token != NULL)
		{
			if (_strcmp("$$", token) == 0)
				cmde = get_process_id();
			else if (_strcmp("$?", token) == 0)
				cmde = get_status(status);
			else if ((token[0] == '$') && (token[1]))
			{
				variable = _getenv(&token[1]);
				if (variable)
					cmde = _strdup(variable);
				else
					cmde = _strdup("");
			}
			else
				cmde = _strdup(token);
			argument_vector[i++] = cmde;
		}
	}
	argument_vector[i] = NULL;
	free(copied_line);
	return (argument_vector);
}
/**
 * flags_handler - flag
 * @token: the token
 * @command: the command
 * @argument_vector: the argument vector
 * @status: the status
 * Return: success or fail
 */
char *flags_handler(char *token, char *command,
		char **argument_vector, int status)
{
	char *variable, *cmde, *copied_line;

	copied_line = command;
	if (token == NULL)
	{
		free(argument_vector);
		free(copied_line);
		return (NULL);
	}
	if (_strcmp("$$", token) == 0)
		cmde = get_process_id();
	else if (_strcmp("$?", token) == 0)
		cmde = get_status(status);
	else if ((token[0] == '$') && (token[1]))
	{
		variable = _getenv(&token[1]);
		if (variable)
			cmde = _strdup(variable);
		else
			cmde = _strdup("");
	}
	else
		cmde = _strdup(token);

	return (cmde);
}

/**
 * number_to_character - Converts an integer to a string.
 * @number: The integer to convert.
 * Return: The string
*/

char *number_to_character(int number)
{
	int count = 0, temprory = number;
	char *copied_number;

	if (number == 0)
		count = 1;
	else
	{
		while (temprory != 0)
		{
			temprory = temprory / 10;
			count++;
		}
	}
	copied_number = malloc(sizeof(char) * (count + 1));
	if (!copied_number)
	{
		perror("malloc error");
		return (NULL);
	}
	copied_number[count] = '\0';

	while (count != 0)
	{
		count--;
		copied_number[count] = '0' + number % 10;
		number = (number / 10);
	}
	return (copied_number);
}
