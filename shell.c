#include "shell.h"

/**
 * main - runs SHELL program (idan)
 * @argc: Argument count.
 * @argv: Argument vector
 * @env: The shell environment
 * Return: Exit status of the program
*/
int main(int argc, char *argv[], char *env[])
{
	int *exit_status, count = 0, non_interactive = 1, status = 0, oper_mode;
	char *command, **command_lines, **cmd_arr = NULL;
	list_paths *path_list;

	exit_status = &status;
	oper_mode = determine_operation_mode(argc);
	if (oper_mode != INTERACTIVE_MODE)
		command_lines = read_command_files(oper_mode, argv[1], argv[0]);
	path_list = convert_paths_to_linkedlist();
	while (non_interactive && ++count)
	{
		if (oper_mode == NON_INTERACTIVE_MODE || oper_mode == NON_INTERACTIVE_PIPE)
		{
			if (command_lines[count - 1])
				command = command_lines[count - 1];
			else
			{
				free(command_lines);
				break;
			}
		}
		else if (oper_mode == INTERACTIVE_MODE)
			command = get_user_input(path_list);
		if (!command)
			continue;
		cmd_arr = split_command_line(command, exit_status);
		if (!cmd_arr)
		{
			free(command);
			continue;
		}
		if (check_dir(cmd_arr[0], argv, count, cmd_arr, exit_status, command) == 0)
			continue;
		if (handle_builtin(command, cmd_arr, path_list, argv[0],
					count, exit_status, NULL, command_lines, argv) != 0)
			handle_nonbuiltin(cmd_arr, env, exit_status, count, path_list, argv);
		free_all(command, cmd_arr);
	}
	free_linkedlist(path_list);
	exit(*exit_status);
}
