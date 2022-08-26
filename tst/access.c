#include <unistd.h>
#include <stdio.h>

int main()
{
	int i = access("/Users/hameur/Documents/Cercle_III/Minishell/ts", F_OK);
	printf("access : %d\n", i);
	//use command chmod to ......
}