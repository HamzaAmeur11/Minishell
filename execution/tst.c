#include <stdio.h>

int main(int ac, char **av, char **env)
{
	int i = -1;
	(void)ac;
	(void)av;
	while (env[++i] != NULL)
		printf("%s\n", env[i]);
}