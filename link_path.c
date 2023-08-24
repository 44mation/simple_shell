#include "shell.h"

/**
 * paths_to_linkedlist - a function that returns a linked list of paths
 * Return: a linked list
*/
list_paths *paths_to_linkedlist()
{
	list_paths *paths_linkedlists;
	char *copied_variable, *path_variable, *token;

	paths_linkedlists = NULL;

	/*getting the PEV and store it at a pointer to char*/
	path_variable = _getenv("PATH");
	if (path_variable == NULL)
		return (NULL);
	/*copying PEV to a new one to start handling it*/
	copied_variable = _strdup(path_variable);
	if (copied_variable == NULL)
		return (NULL);
	/*Tokenising the New PEV by (:) delimeter*/
	token = strtok(copied_variable, ":");
	while (token != NULL)/*looping tell the end*/
	{
		/*adding each token in path as a node in LL */
		add_node(&paths_linkedlists, token);
		/*
		 * each call will return the next token in the
		 * string until there are no more tokens left
		 */
		token = strtok(NULL, ":");
	}
	free(copied_variable);
	/*
	 * returns a linked list, which contains the paths extracted from
	 * the "PATH" environment variable.
	 */
	return (paths_linkedlists);
}

/**
 * add_node - a function that adds a new node at the beginning of a list_t list
 * @head: pointer to the head of list with the type list_paths
 * @path: pointer to path.
 * Return: the address of the new element, or NULL if it failed
 */
list_paths *add_node(list_paths **head, char *path)
{
	list_paths *new;
	int i = 0;
	char *string_path;


	/*getting the count of elements (i), in str array of chars*/
	while (path[i] != '\0')
	{
		i++;
	}
	/*allocating memory to new node with type list_paths*/
	new = malloc(sizeof(list_paths));
	/*assuring it doesn't point to NULL*/
	if (new == NULL)
		return (NULL);

	if (path)
	{
		/*duplicating the contents of path in path element of the new node created*/
		string_path = _strdup(path);
		if (string_path == NULL)
		{
			free(new);
			return (NULL);
		}
		/*updating len element with the length of the new path entered*/
		new->len = i;
		new->path = string_path;
	}
	else
	{
		new->len = 0;
		new->path = NULL;
	}
	/*updating the next pointer with a pointer to the new node*/
	new->next = (*head);

	*head = new;
	return (new);
}

/**
 * free_linkedlist - Frees a singly linked list
 * @list_head: Pointer to the head of the list
*/

void free_linkedlist(list_paths *list_head)
{
	list_paths *current_node = list_head;
	list_paths *next_node;

	while (current_node != NULL)
	{
		next_node = current_node->next;
		free(current_node->path);
		free(current_node);
		current_node = next_node;
	}
}

/**
 * print_list - prints all the elements of a list_paths list
 * If str is NULL, print [0] (nil)
 * @h: pointer to the head of list with the type list_paths
 * Return: the number of nodes
 */
size_t print_list(const list_paths *h)
{
	int count;

	if (h == NULL)
	{
		return (0);
	}
	count = 0;
	while (h)
	{
		if (h->path == NULL)
		{
			printf("[0] (nil)\n");
			fflush(stdout);
		}
		else
		{
			printf("[%d] %s\n", h->len, h->path);
			fflush(stdout);
		}
		h = h->next;
		count++;
	}
	return (count);
}
