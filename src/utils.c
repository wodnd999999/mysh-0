#include "utils.h"
#include <malloc.h>

#define MAX 8096

void mysh_parse_command(const char* command,
                        int *argc, char*** argv)
{
	int state = 0;
	int count = 0;
	int start[MAX], end[MAX];
	int i, j;

	for(i = 0; command[i]; i++)
	{
		switch(state)
		{
		case 0:
			if(!(command[i] == ' ' || command[i] == '\t' || command[i] == '\n'))
			{
				state = 1;
				start[count] = i;
			}
			break;
		case 1:
			if(command[i] == ' ' || command[i] == '\t' || command[i] == '\n')
			{
				state = 0;
				end[count] = i;
				count++;
			}
			break;
		}
	}
	if(state == 1)
		end[count++] = i;

	if(count)
	{
		(*argc) = count;
		(*argv) = (char**)malloc(sizeof(char*) * count);
		for(i = 0; i < count; i++)
		{
			(*argv)[i] = (char*)malloc(sizeof(char) * (end[i] - start[i] + 1));
			for(j = start[i]; j < end[i]; j++)
				(*argv)[i][j - start[i]] = command[j];
			(*argv)[i][end[i] - start[i]] = '\0';
		}
	}
	else
	{
		(*argc) = 1;
		(*argv) = (char**)malloc(sizeof(char*));
		(*argv)[0] = (char*)malloc(sizeof(char));
		(*argv)[0][0] = '\0';
	}
}
