#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

int main()
{
	/*	pid_t fork(void);
	**fork() : creates a new process by duplicating the calling process.
    **The new process is referred to as the child process.  The calling
    **process is referred to as the parent process.*/

	int id = fork();
	if (id == 0)
		printf("child prossec %d have a pid : %d\n",id, getpid());
	else
		printf("parent prossec %d have a pid : %d\n",id, getpid());
	if (id == 0){
		sleep(2);
		printf("child prossec %d have a pid : %d\n",id, getpid());
	}
	// wait(NULL);
	return (0);
}