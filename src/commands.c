#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "commands.h"

int do_cd(int argc, char ** argv)
{
	if (!validate_cd_argv(argc, argv))
		return -1;
	else
		return chdir(argv[1]);
}

int do_pwd(int argc, char ** argv)
{
	char *buf;

	if (!validate_pwd_argv(argc, argv))
		return -1;

	if (buf = getcwd(NULL, 0))
	{
		puts(buf);
		free(buf);
		return 0;
	}
	else
		return -1;
}

int validate_cd_argv(int argc, char ** argv)
{
	if (argc != 2)
		return 0;
	else if (strcmp(argv[0], "cd"))
		return 0;
	else
		return 1;
}

int validate_pwd_argv(int argc, char ** argv)
{
	if (argc != 1)
		return 0;
	else if (strcmp(argv[0], "pwd"))
		return 0;
	else
		return 1;
}
