#include "mini.h"


void ft_free(char **str)
{
	int i;

	i = -1;
	while(str[++i])
		free(str[i]);
	free(str);
}

int ff(char **env)
{
	/*char *readline(const char *prompt)

	**read a line from the terminal and return it "ise flag -lreadline"
	** add_history() add a history of line return by readline*/
	char *line;
	char **str;
	int id = 1;
	while(1)
	{
		line = readline("Minishel => ");
		int i = ft_strlen(line);
		str = ft_split(line, ' ');
		if (i != 0)
			add_history(line);
		if (id > 0)
			id = fork();
		if (id == 0)
			execute_cmnd(str, env);
		if(id > 0)
			wait(NULL);
	}
	return (SUCCESS);
}

int main(int ac, char **av, char **env)
{

	ff(env);
	return (SUCCESS);
}