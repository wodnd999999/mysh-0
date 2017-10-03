#include <malloc.h>

#include "utils.h"

typedef struct TOKEN
{
	int		start;
	int		end;
	struct TOKEN	*next;
} TOKEN;

void mysh_parse_command(const char *command, int *argc, char ***argv)
{
	int	state = 0;
	int	count = 0;
	TOKEN	*head = NULL;
	TOKEN	*tail = NULL;
	int	i, j, k;

	for (i = 0; command[i]; i++)
	{
		switch (state)
		{
		case 0:
			if (!(command[i] == ' ' || command[i] == '\t' || command[i] == '\n'))
			{
				state = 1;
				count++;
				if (head)
					tail = tail->next = (TOKEN*) malloc(sizeof(TOKEN));
				else
					head = tail = (TOKEN*) malloc(sizeof(TOKEN));
				tail->start = i;
				tail->next = NULL;
			}
			break;
		case 1:
			if (command[i] == ' ' || command[i] == '\t' || command[i] == '\n')
			{
				state = 0;
				tail->end = i;
			}
			break;
		}
	}
	if (state == 1)
		tail->end = i;

	if (count)
	{
		(*argc) = count;
		(*argv) = (char **) malloc(sizeof(char *) * count);
		for(i = 0; i < count; i++)
		{
			(*argv)[i] = (char *) malloc(sizeof(char) * (head->end - head->start + 1));
			for(j = head->start, k = 0; j < head->end; j++, k++)
				(*argv)[i][k] = command[j];
			(*argv)[i][k] = '\0';
			tail = head;
			head = head->next;
			free(tail);
		}
	}
	else
	{
		(*argc) = 1;
		(*argv) = (char **) malloc(sizeof(char *));
		(*argv)[0] = (char *) malloc(sizeof(char));
		(*argv)[0][0] = '\0';
	}
}
