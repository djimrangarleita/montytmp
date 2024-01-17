#include "monty.h"

/**
 * execcmd - read file and executes cmds
 * @filename: name of the file to read cmds from
 * @stack: head ptr to stack
 * Return: nothing
 */
int execcmd(char *filename, stack_t **stack)
{
	int status = 1;
	FILE *stream;

	stream = fopen(filename, "r");

	if (stream == NULL)
	{
		dprintf(STDERR_FILENO, "Error: Can't open file %s\n", filename);
		return (status);
	}
	status = get_inputs(stream, stack);
	fclose(stream);

	return (status);
}

/**
 * runcmd - execute the monty cmd
 * @cmd: ptr to cmd and list of args
 * @line_number: line where the cmd was red
 * @stack: head ptr to stack
 * Return: execution status
 */
int runcmd(char **cmd, unsigned int line_number, stack_t **stack)
{
	int i = 0;
	instruction_t flist[] = {
		{"pall", pall},
		{"pint", pint},
		{"pop", pop},
		{"swap", swap},
		{"add", add},
		{NULL, NULL}
	};

	if (strcmp("nop", cmd[0]) == 0 && cmd[1] == NULL)
	{
		free_toks(cmd);
		return (0);
	}
	if (strcmp("push", cmd[0]) == 0)
	{
		push(stack, cmd, line_number);
		return (0);
	}
	else
	{
		while (flist[i].opcode != NULL)
		{
			if (strcmp(flist[i].opcode, cmd[0]) == 0 && cmd[1] == NULL)
			{
				free_toks(cmd);
				flist[i].f(stack, line_number);
				return (0);
			}
			i++;
		}
	}
	dprintf(STDERR_FILENO, "L%u: unknown instruction", line_number);
	while (cmd && *cmd)
		dprintf(STDERR_FILENO, " %s", *cmd++);
	printf("\n");

	return (1);
}