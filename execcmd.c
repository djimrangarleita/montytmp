#include "monty.h"

/**
 * execcmd - read file and executes cmds
 * @filename: name of the file to read cmds from
 * @stack: head ptr to stack
 * Return: nothing
 */
int execcmd(char *filename, stack_t **stack)
{
	FILE *stream;

	stream = fopen(filename, "r");

	if (stream == NULL)
	{
		dprintf(STDERR_FILENO, "Error: Can't open file %s\n", filename);
		return (status);
	}
	get_inputs(stream, stack);
	fclose(stream);

	return (status);
}

/**
 * runcmd - execute the monty cmd
 * @cmd: ptr to cmd and list of args
 * @line_number: line where the cmd was red
 * @stack: head ptr to stack
 * @is_stack: check if push to stack = 0 or queue = 1
 * Return: execution status
 */
int runcmd(char **cmd, unsigned int line_number, stack_t **stack, int is_stack)
{
	int i = 0;
	instruction_t flist[] = {
		{"pall", pall}, {"pint", pint}, {"pop", pop}, {"swap", swap},
		{"add", add}, {"sub", sub}, {"div", divide}, {"mul", mul}, {"mod", mod},
		{"pchar", pchar}, {"pstr", pstr}, {"rotl", rotl}, {"rotr", rotr},
		{NULL, NULL}
	};

	if (strcmp("nop", cmd[0]) == 0 && cmd[1] == NULL)
		return (0);
	if (strcmp("push", cmd[0]) == 0)
	{
		push(stack, cmd, line_number, is_stack);
		return (0);
	}
	else
	{
		while (flist[i].opcode != NULL)
		{
			if (strcmp(flist[i].opcode, cmd[0]) == 0 && cmd[1] == NULL)
			{
				flist[i].f(stack, line_number);
				return (0);
			}
			i++;
		}
	}
	dprintf(STDERR_FILENO, "L%u: unknown instruction", line_number);
	status = 1;
	while (cmd && *cmd)
		dprintf(STDERR_FILENO, " %s", *cmd++);
	dprintf(STDERR_FILENO, "\n");

	return (1);
}
