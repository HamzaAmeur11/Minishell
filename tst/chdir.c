#include<unistd.h>
#include<stdio.h>
#include <fcntl.h>
#include <string.h>


int main()
{
	char *path = getcwd(NULL, 0);
	printf("%s\n", path);
	if (chdir("/") != 0)
		return(1);
	path = getcwd(NULL, 0);
	printf("%s\n", path);
}