#include "mini.h"
#include <sys/types.h>
#include <sys/wait.h>

//protect all malloc in your minishell





int	exec_cmnd(t_global *global)
{
	t_cmnd *cmnd;
	int		red_type = 0;
	int		pid = fork();
	if (pid == 0)
	{
		cmnd = initializ_cmnd(global);
		red_type = type_red(global->cmnd_list);
		if (red_type == R_OUT || red_type == DR_OUT)
			redirection_out(name_red(global->cmnd_list), red_type);
		else if (red_type == R_INP || red_type == DR_INP)
			redirection_inp(name_red(global->cmnd_list), red_type);
		if (builtin_fct(cmnd, &global->env) != SUCCESS)
		{
			if (other_fct(cmnd, &global->env) != SUCCESS)
				return (write(2 ,"error\n", 6), exit(1), FAILDE);//exit bwhd int
		}
	}
	else
	{
		wait(NULL);
		unlink(".heredoc");
	}
	return (0);
}


int ff(t_global *global)
{
	char *line;
	while(1)
	{
		line = readline("Minishel => ");
		int j = ft_strlen(line);
		if (j != 0)
			add_history(line);
		if (j == 0)
			continue ;
		init_list(&global->cmnd_list, line);
		exec_cmnd(global);
	}
	return (SUCCESS);
}

int main(int ac, char **av, char **env)
{
	t_global *global;
	global = (t_global *)malloc(sizeof(t_global));
	global->env = init_envi(env);

	//env valide
	(void)ac;(void)av;

	ff(global);
	return (SUCCESS);
}
