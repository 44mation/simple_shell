#ifndef SHELL_H_
#define SHELL_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

/* read & write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* command chain */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* convert number */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* system getline */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;


/**
 * struct liststr - singly linked list
 * @num: the number
 * @str: string
 * @next: next node
*/
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 * struct passinfo - pseudo-arguements to pass into a function
 * @arg: a string from getline contain arguements
 * @argv: array of strings
 * @path: a string path for current command
 * @argc: argument count
 * @line_count: error count
 * @err_num: error code for exit()
 * @linecount_flag: count line of input
 * @fname: filename
 * @env: linked list copy
 * @environ: modified copy of environ
 * @history: history node
 * @alias: alias node
 * @env_changed: environ changed
 * @status: status of the last command
 * @cmd_buf: address of pointer to cmd_buf
 * @cmd_buf_type: CMD type
 * @readfd: read line input
 * @histcount: count of history
*/
typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;
	char **cmd_buf;
	int cmd_buf_type;
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
			0, 0, 0}

/**
 * struct builtin - builtin string & related function
 * @type: command flag
 * @func: the function
*/
typedef struct builtin
{
		char *type;
			int (*func)(info_t *);
} builtin_table;


/* shloop.c */
int hsh(info_t *, char **);
int find_builtin(info_t *);
void find_cmd(info_t *);
void fork_cmd(info_t *);

/* parser.c */
int is_cmd(info_t *, char *);
char *dup_chars(char *, int, int);
char *find_path(info_t *, char *, char *);

/* loophsh.c */
int loophsh(char **);

/* errors.c */
void _eputs(const char *str);
int _eputchar(char c);
int _putfd(char c, int fd);
int _putsfd(const char *str, int fd);

/* string.c */
int custom_strlen(char *);
int custom_strcmp(char *, char *);
char *custom_starts_with(const char *, const char *);
char *custom_strcat(char *, char *);

/* string1.c */
char *_strcpy(char *, const char *);
char *_strdup(const char *);
void _puts(const char *);
int _putchar(char);

/* builtin.c */
int _myexit(info_t *);
int _mycd(info_t *);
int _myhelp(info_t *);

/* builtin1.c */
int _myhistory(info_t *);
int _myalias(info_t *);
int set_alias(info_t *, char *);
int unset_alias(info_t *, char *);
int print_alias(list_t *);

/* tokenizer.c */
char **strtow(char *, char *);
char **strtow2(char *, char);

/* realloc.c */
char *_memset(char *, char, unsigned int);
void ffree(char **);
void *_realloc(void *, unsigned int, unsigned int);

/* memory.c */
int bfree(void **);

/* _atoi.c */
int interactive(info_t *);
int is_delim(char, char *);
int _isalpha(int);
int _atoi(char *);

/* errors1.c */
int _erratoi(char *);
void print_error(info_t *, char *);
int print_d(int, int);
char *convert_number(long int, int, int);
void remove_comments(char *);

/* getline.c */
ssize_t get_input(info_t *);
int _getline(info_t *, char **, size_t *);
void sigintHandler(int);

/* getinfo.c */
void clear_info(info_t *);
void set_info(info_t *, char **);
void free_info(info_t *, int);

/* environ.c */
char *_getenv(info_t *, const char *);
int _myenv(info_t *);
int _mysetenv(info_t *);
int _myunsetenv(info_t *);
int populate_env_list(info_t *);

/* getenv.c */
char **get_environ(info_t *);
int _unsetenv(info_t *, char *);
int _setenv(info_t *, char *, char *);

/* history.c */
char *get_history_file(info_t *info);
int write_history(info_t *info);
int read_history(info_t *info);
int build_history_list(info_t *info, char *buf, int linecount);
int renumber_history(info_t *info);

/* lists.c */
list_t *add_node(list_t **, const char *, int);
list_t *add_node_end(list_t **, const char *, int);
size_t print_list_str(const list_t *);
int delete_node_at_index(list_t **, unsigned int);
void free_list(list_t **);

/* lists1.c */
size_t list_len(const list_t *);
char **list_to_strings(list_t *);
size_t print_list(const list_t *);
list_t *node_starts_with(list_t *, char *, char);
ssize_t get_node_index(list_t *, list_t *);

/* vars.c */
int is_chain(info_t *, char *, size_t *);
void check_chain(info_t *, char *, size_t *, size_t, size_t);
int replace_alias(info_t *);
int replace_vars(info_t *);
int replace_string(char **, char *);

/* exits.c */
char *_strncpy(char *, const char *, size_t);
char *_strncat(char *, const char *, size_t);
char *_strchr(const char *, char);

/* vars.c */
int is_command_chain_delimiter(info_t *, char *, size_t *);
void check_command_chain(info_t *, char *, size_t *, size_t, size_t);
int replace_alias_in_arguments(info_t *);
int replace_variables_in_arguments(info_t *);
int replace_string_in_arguments(char **, char *);

#endif
