#include"shell.h"

/**
* nonbuiltin_hndler - Handles non-builtin commands
* @command_array: Array of command arguments
* @env: Environment variables
* @status: Pointer to the variable 'status'
* @count: Number of commands executed
* @current: Pointer to the list_paths structure
* @argv: Array of command-line arguments (argument vector)
* This function handles non-builtin commands in the shell
* by checking the access permissions of the commands.
*/
void nonbuiltin_hndler(char **command_array, char *env[], int *status,
						int count, list_paths *current, char *argv[])
{
char *new_path;

if (access(command_array[0], X_OK) == 0)
command_executer(command_array[0], command_array, env, status);
else
{
/*if the user enters the command without the whole path*/
new_path = check_access(command_array[0], current);
if (new_path)
{
command_executer(new_path, command_array, env, status);
free(new_path);
}
else
{
print_error(argv[0], count, command_array[0], NOT_FOUND);/*----lsa----*/
*status = NOT_FOUND;
}
}
}

/**
 * noninteractive_files_handler - processes shell commands in a file
 * @file_name: name of file with shell commands
 * @shell_name: name of shell to use
 * Return: pointer to char array with output
 * Opens file, reads each line.
 * pointer to char array with output.
 */
char **noninteractive_files_handler(char *file_name, char *shell_name)
{
struct stat fileStat;
char *text, **command_lines;
size_t letters_read;
int fd;

if (stat(file_name, &fileStat) != -1)
{
if (S_ISREG(fileStat.st_mode))
{
fd = open(file_name, O_RDONLY);
if (fd  == -1)
exit(ERROR);
if (fileStat.st_size == 0)
exit(0);
text = malloc((fileStat.st_size + 1) * sizeof(char));
if (!text)
return (NULL);
letters_read = read(fd, text, fileStat.st_size);
if ((int) letters_read == -1)
{
perror("reading error");
}
close(fd);
text[letters_read - 1] = '\0';
if (text)
command_lines = text_to_array(text);
return (command_lines);
}
else
exit(0);
}
else
{
cant_open_handler(shell_name, 0, file_name);
exit(127);
}
return (NULL);
}

/**
 * noninteractive_pipes_handler - processes shell commands with pipes
 * Return: pointer to char array with output
 */
char **noninteractive_pipes_handler()
{
char c[2048], *text_read, **command_lines;
size_t total_characters_read = 0;
ssize_t bytes_read;
int i, flags;

flags = 0;
command_lines = NULL;
text_read = NULL;
while ((bytes_read = read(STDIN_FILENO, c, 2048)) > 0)
{
total_characters_read = total_characters_read + bytes_read;
}
if (bytes_read == -1)
{
perror("reading error");
exit(ERROR);
}
if (total_characters_read > 2048)
c[2048 - 1] = '\0';
else
c[total_characters_read - 1] = '\0';

for (i = 0; c[i]; i++)
{
if (c[i] != ' ')
flags = 1;
}
if (flags == 0)
return (NULL);
total_characters_read = _strlen(c);
text_read = (char *)malloc(sizeof(char) * (total_characters_read + 1));
if (text_read != NULL)
{
_strcpy(text_read, c);
text_read[total_characters_read] = '\0';
command_lines = text_to_array(text_read);
}
return (command_lines);
}
