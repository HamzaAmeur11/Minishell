#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>


int x;

int main()
{
	/*	pid_t fork(void);
	**fork() : creates a new process by duplicating the calling process.
    **The new process is referred to as the child process.  The calling
    **process is referred to as the parent process.*/

	int id = fork();
	if (id == 0)
	{
		while (x < 10)
			x++;
			printf("child proc : x = %d\n", x);
	}
	else
	{
		sleep(2);
		printf("parent proc  : x = %d\n", x);
	}
	// wait(NULL);
	return (0);
}