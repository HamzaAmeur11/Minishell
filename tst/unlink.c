#include <unistd.h>
#include <stdio.h>

int main()
{
	char *path = getcwd(NULL, 0);
	printf("%s\n", path);
	//creat a file named "a" 
	unlink("a");
}