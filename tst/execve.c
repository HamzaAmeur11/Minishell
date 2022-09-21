#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>


int main(int ac, char **av, char **envp)
{
	int i = 0;
	(void)ac;
	(void)av;
	char *args[3];
	args[0] = "ls";
	args[1] = "-la";
	args[2] = NULL;
	int fd = open("file.txt",O_CREAT | O_RDWR | O_TRUNC);
	dup2(fd, 1);
	printf("tst redjhaehhhhhhhhhhhhhhs\n");
	char scan[100];
	while (1)
	{
		scanf("%s\n", scan);
		printf("%s\n", scan);
	}
	/*if (execve("/usr/bin/ls", args, envp) < 0)
		printf("error\n");
	dup2(STDOUT_FILENO, fd);
	execve("ls", args, envp);*/
}