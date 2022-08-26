#include <unistd.h>
#include <stdio.h>


int main(int ac, char **av, char **envp)
{
	int i = 0;
	(void)ac;
	(void)av;
	while (envp[i] != NULL)
		printf("%s\n", envp[i++]);
}