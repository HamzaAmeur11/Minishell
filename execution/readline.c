#include "mini.h"


void ft_free(char **str)
{
	int i;

	i = -1;
	while(str[++i])
		free(str[i]);
	free(str);
}

int ff(t_envi **env)
{
	/*char *readline(const char *prompt)

	**read a line from the terminal and return it "ise flag -lreadline"
	** add_history() add a history of line return by readline*/
	char *line;
	char **cmnd;
	int id = 1;
	while(1)
	{
		line = readline("Minishel => ");
		int j = ft_strlen(line);
		cmnd = ft_split(line, ' ');
		if (j != 0)
			add_history(line);
		if (j == 0)
			continue ;
		int i = builtin_fct(cmnd, env);
		if (id > 0 && i != SUCCESS)
			id = fork();
		if (id == 0)
		{
			if (other_fct(cmnd, env) != SUCCESS)
				return(printf("eroor f execution\n"), ft_free(cmnd), FAILDE);
			ft_free(cmnd);
		}
		if(id > 0 && i != SUCCESS)
		{
			wait(NULL);
			ft_free(cmnd);
		}

	}
	return (SUCCESS);
}

int main(int ac, char **av, char **env)
{
	t_envi *envi;
	envi = init_envi(env);
	ff(&envi);
	return (SUCCESS);
}