#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int ac, char **av, char **env)
{
	char **cmnd;
	cmnd = (char **)malloc(sizeof(char *));
	cmnd[0] = (char *)malloc(sizeof(char) * 3);
	cmnd[1] = (char *)malloc(sizeof(char) * 3);
	cmnd[2] = (char *)malloc(sizeof(char) * 3);
	cmnd[0] = "ls";
	cmnd[1] = "-la";
	cmnd[2] = NULL;

	execve("/bin/ls", cmnd, env);
	while(1);
}
