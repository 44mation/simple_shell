#include "shell.h"

/**
 * interactive - returns true if shell is in interactive mode
 * @info: struct address
 * Return: false or true (0 or 1)
*/
int interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_delim - checks character is a delimiter
 * @c: the char to check
 * @delime: the delimiter
 * Return: true or false
*/
int is_delim(char c, char *delime)
{
	while (*delime)
	{
		if (*delime == c)
		{
			return (1);
		}
		delime++;
	}
	return (0);
}

/**
 * _isalpha - checks for alphabetic character
 * @c: The character to input
 * Return: 1 if c is alphabetic, 0 otherwise
*/
int _isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
	{
		return (1);
	}
	else
	{
		return (0);
	}
}
/**
 * _atoi - converts a string to an integer
 * @s: the string to convert
 * Return: true or false
*/
int _atoi(char *s)
{
	int i, sign = 1, flag = 0, output;
	unsigned int res = 0;

	for (i = 0; s[i] != '\0' && flag != 2; i++)
	{
		if (s[i] == '-')
			sign *= -1;
		if (flag == 1)
			flag = 2;
		else if (s[i] >= '0' && s[i] <= '9')
		{
			flag = 1;
			res *= 10;
			res += (s[i] - '0');
		}
	}
	if (sign == -1)
		output = -res;
	else
		output = res;
	return (output);
}
