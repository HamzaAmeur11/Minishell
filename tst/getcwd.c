#include <unistd.h>
#include <stdio.h>

int main()
{
	/*	char *getcwd(char *buf, size_t size);
	**These functions return a null-terminated string containing an
    **absolute pathname that is the current working directory of the
	**calling process
	*/
	char *str = (char *)"/Users/hameur/Documents";
	str = getcwd("/Users/hameur/Documents", 20);
	printf("%s\n", str);
}