#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <fcntl.h>

int execute_cmnd(char *str, char *flag, char *finish, int inp, int out, int key)
{
	int id = fork();
	if (id < 0)
		return 1;
	if (id == 0)
	{
		if (key == 0)
			dup2(inp, 0);
		else if (key == 1)
			dup2(out, 1);
		execlp(str ,str, flag, finish);
	}
	if (id > 0)
	{
		wait(NULL);
		close(inp);
		close(out);
	}
	return 0;

}

int main()
{
	/*	pid_t fork(void);
	**fork() : creates a new process by duplicating the calling process.
    **The new process is referred to as the child process.  The calling
    **process is referred to as the parent process.*/

	//execute : cat fork.c | wc -l

	int fd[2];
	pipe(fd);
	if (execute_cmnd("cat", "fork.c", NULL, 0, fd[1], 1) != 0)
		return (write (2 ,"error a zbi \n", 14), 1);
	execute_cmnd("wc", "-l", NULL, fd[0], 1, 0);




	// wait(NULL);
	return (0);
}
