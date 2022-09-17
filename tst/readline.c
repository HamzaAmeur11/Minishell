#include <unistd.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <string.h>
int main()
{
	/*char *readline(const char *prompt)
	**read a line from the terminal and return it "ise flag -lreadline"
	** add_history() add a history of line return by readline*/
	char *line;
	
		line = readline("Minishel => ");
		printf("%s\n", line);
		int i = strlen(line);
		if (i != 0)
			add_history(line);

}