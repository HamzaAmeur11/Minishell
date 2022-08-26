#include<unistd.h>
#include<stdio.h>
#include <fcntl.h>

int main()
{
	char *path = getcwd(NULL, 0);
	printf("%s\n", path);
	if (chdir("llll") != 0)
		return(1);
	path = getcwd(NULL, 0);
	printf("%s\n", path);
	open("")
}