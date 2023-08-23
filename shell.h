#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

#define NOT_FOUND 127
#define PERMISSION_DENIED 126
#define EXIT_ERROR 2

#define INTERACTIVE_MODE 1
#define NON_INTERACTIVE_PIPE 2
#define NON_INTERACTIVE_MODE 0
#define ERROR -1
#define TOK_D " \t\r\n\a\""


/**
 * struct list_paths - a struct for nodes out of enviroment
 * @path: enviroment variable path
 * @len: length of the path
 * @next: points to the next node
*/
typedef struct list_paths
{
	char *path;
	unsigned int len;
	struct list_paths *next;
} list_paths;

int handle_builtin(char *command, char **command_array, list_paths *current,
		char *shell_name, int count, int *status,
		list_paths *env_list, char **command_lines, char **argv);
void cant_open_handler(char *program_name, int counter, char *file_name);
unsigned int char_count(char *string, char character);
int check_dir(char *command, char **argument_vector, int count,
		char **command_array, int *status, char *command_line_before);

char *check_access(char *command, list_paths *current);
char *check_input_file(char *file);
int check_mode(int argc);
int _cd(char **command_array, char **argument_vector);
void _setenv(char *key, char *value, list_paths *current);

void command_execute(char *path, char **av, char **env, int *status);

void exit_handler(char *command, char **command_array, list_paths *current,
		char *shell_name, int count, int *status,
		list_paths *env, char **command_lines);
void free_whole(char **command_lines, int count, list_paths *env,
		list_paths *current, char *command, char **command_array);
void free_all(char *command, char **command_array);
void free_array(char **argv);
void free_vector(char **vector);

int _atoi(char *s);
char *_getenv(const char *name);
char *_strtok(char *str, const char *delimiters);
char **text_to_array(char *text_read);

char *get_process_id();
char *get_status(int n);
void handle_comments(char *input);

list_paths *paths_to_linkedlist();
list_paths *add_node(list_paths **head, char *path);
void free_linkedlist(list_paths *list_head);
size_t print_list(const list_paths *h);

void handle_nonbuiltin(char **command_array, char *env[], int *status,
		int count, list_paths *current, char *argv[]);
char **noninteractive_files_handler(char *file_name, char *shell_name);
char **noninteractive_pipes_handler();

char *scan_cmd_user(list_paths *current);
char **scan_command_files(int op_mode, char *file_name, char *shell_name);

void int_to_str(int n, char *str);
int line_count(char *line);
char **line_to_vector(char *command, int status);
char *flags_handler(char *token, char *command,
		char **argument_vector, int status);
char *number_to_character(int number);

int _strlen(char *s);
char *_strdup(char *str);
int _strcmp(char *s1, char *s2);
char *_strcpy(char *dest, char *src);
char *_strcat(char *dest, char *src);

unsigned int piped_characters_count(char *string, char c);
void print_env(int *status);
void print_error(char *shell_name, int count,
		char *command_array, int type_of_error);
char *process_token(char *token, int status);

#endif
