#include "shell.h"

/**
 * _strncpy - copies a string
 * @dest: the destination string to be copied to
 * @src: the source string
 * @n: the number of characters to be copied
 * Return: the pointer to the destination string
*/
char *_strncpy(char *dest, const char *src, size_t n)
{
	char *original_dest = dest;

	while (*src && n > 0)
	{
		*dest = *src;
		dest++;
		src++;
		n--;
	}

	while (n > 0)
	{
		*dest = '\0';
		dest++;
		n--;
	}

	return (original_dest);
}

/**
 * _strncat - concatenates two strings
 * @dest: the destination string
 * @src: the source string
 * @n: the maximum number of characters to be appended
 * Return: the pointer to the concatenated string
*/
char *_strncat(char *dest, const char *src, size_t n)
{
	char *original_dest = dest;

	while (*dest)
	{
		dest++;
	}

	while (*src && n > 0)
	{
		*dest = *src;
		dest++;
		src++;
		n--;
	}

	*dest = '\0';

	return (original_dest);
}

/**
 * _strchr - locates a character in a string
 * @s: the string to be parsed
 * @c: the character to look for
 * Return: a pointer to the first occurrence of c in s, or NULL if not found
*/
char *_strchr(const char *s, char c)
{
	while (*s)
	{
		if (*s == c)
		{
			return ((char *)s);
		}
		s++;
	}

	if (c == '\0')
	{
		return ((char *)s);
	}

	return (NULL);
}
