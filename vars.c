#include "shell.h"

/**
 * is_command_chain_delimiter - Checks if the current character in the buffer is a command chain delimiter
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * @buf: The character buffer
 * @position: Address of the current position in buf
 * Return: 1 if the character is a command chain delimiter, 0 otherwise
 */
int is_command_chain_delimiter(info_t *info, char *buf, size_t *position)
{
	size_t j = *position;

	if (buf[j] == '|' && buf[j + 1] == '|')
	{
		buf[j] = 0;
		j++;
		info->command_buffer_type = COMMAND_OR;
	}
	else if (buf[j] == '&' && buf[j + 1] == '&')
	{
		buf[j] = 0;
		j++;
		info->command_buffer_type = COMMAND_AND;
	}
	else if (buf[j] == ';')
	{
		buf[j] = 0;
		info->command_buffer_type = COMMAND_CHAIN;
	}
	else
		return (0);

	*position = j;
	return (1);
}

/**
 * check_command_chain - Checks whether we should continue chaining based on the last command status
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * @buf: The character buffer
 * @position: Address of the current position in buf
 * @i: Starting position in buf
 * @len: Length of buf
 * Return: Void
 */
void check_command_chain(info_t *info, char *buf, size_t *position, size_t i, size_t len)
{
	size_t j = *position;

	if (info->command_buffer_type == COMMAND_AND)
	{
		if (info->status)
		{
			buf[i] = 0;
			j = len;
		}
	}
	if (info->command_buffer_type == COMMAND_OR)
	{
		if (!info->status)
		{
			buf[i] = 0;
			j = len;
		}
	}

	*position = j;
}

/**
 * replace_alias_in_arguments - Replaces aliases in the tokenized argument array
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: 1 if alias was replaced, 0 otherwise
 */
int replace_alias_in_arguments(info_t *info)
{
	int i;
	list_t *node;
	char *p;

	for (i = 0; i < 10; i++)
	{
		node = find_alias_with_prefix(info->alias, info->arguments[0], '=');
		if (!node)
			return (0);
		free(info->arguments[0]);
		p = _strchr(node->str, '=');
		if (!p)
			return (0);
		p = _strdup(p + 1);
		if (!p)
			return (0);
		info->arguments[0] = p;
	}
	return (1);
}

/**
 * replace_variables_in_arguments - Replaces variables in the tokenized argument array
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: 1 if variables were replaced, 0 otherwise
 */
int replace_variables_in_arguments(info_t *info)
{
	int i = 0;
	list_t *node;

	for (i = 0; info->arguments[i]; i++)
	{
		if (info->arguments[i][0] != '$' || !info->arguments[i][1])
			continue;

		if (!_strcmp(info->arguments[i], "$?"))
		{
			replace_string_in_arguments(&(info->arguments[i]),
					_strdup(convert_number(info->status, 10, 0)));
			continue;
		}
		if (!_strcmp(info->arguments[i], "$$"))
		{
			replace_string_in_arguments(&(info->arguments[i]),
					_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = find_alias_with_prefix(info->environment, &info->arguments[i][1], '=');
		if (node)
		{
			replace_string_in_arguments(&(info->arguments[i]),
					_strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		replace_string_in_arguments(&info->arguments[i], _strdup(""));
	}
	return (0);
}

/**
 * replace_string_in_arguments - Replaces a string in the arguments array
 * @old: Address of the old string
 * @new: New string
 * Return: 1 if string was replaced, 0 otherwise
 */
int replace_string_in_arguments(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}

