#include "mini.h"
#include <sys/types.h>
#include <sys/wait.h>

//protect all malloc in your minishell




int	exec_cmnd(t_list *cmnd_list, t_envi *env)
{
	t_cmnd *cmnd;
	int		red_type = 0;

	cmnd = initializ_cmnd(cmnd_list, env);
	red_type = type_red(cmnd_list);
	if (red_type == R_OUT || red_type == DR_OUT)
		redirection_out(name_red(cmnd_list), red_type);
	else if (red_type == R_INP || red_type == DR_INP)
		redirection_inp(name_red(cmnd_list), red_type);
	if (builtin_fct(cmnd, &env) != SUCCESS)
	{
		if (other_fct(cmnd, &env) != SUCCESS)
			return (write(2 ,"error\n", 6), exit(1), FAILDE);//exit bwhd int
	}
	return (0);
}



void init_parties(t_global *glb, t_list **left, t_list **right, int pipe_num)
{
	int total_pipes = nbr_mots(glb->cmnd, '|');
	char **str = ft_split(glb->cmnd, '|');
	init_list(left, str[total_pipes - pipe_num]);
	if (str[total_pipes - pipe_num + 1] != NULL)
		init_list(right, str[total_pipes - pipe_num + 1]);
	else
		right = NULL;
	ft_free(str);
}






int ft_pipes(t_global *global, int pipe_num, int *old_fd)
{
	t_list *left_cmnd = NULL;
	t_list *right_cmnd = NULL;


	init_parties(global, &left_cmnd, &right_cmnd, pipe_num);
	int	fd[2];
	if (pipe(fd) < 0)
		return (FAILDE);
	int	pid = fork();
	if (pid < 0)
		return (FAILDE);
	if (pid == 0)
	{
												//execute left cmnd
		if (old_fd != NULL)
		{
			dup2(old_fd[0], STDIN_FILENO);
			close(old_fd[0]);
			close(old_fd[1]);
		}
		if (right_cmnd != NULL)
		{
			dup2(fd[1], STDOUT_FILENO);
			close(fd[0]);
			close(fd[1]);
		}
		if (exec_cmnd(left_cmnd, global->env) != SUCCESS)
			return (FAILDE);
	}
	if (pid > 0)
	{
												//wait child procces
												//execute right cmnd
		//close(fd[0]);
		//close(fd[1]);
		if (old_fd != NULL)
		{
			close(old_fd[0]);
			close(old_fd[1]);
		}
		//close(fd[0]);
		//close(fd[1]);
		wait(NULL);
		unlink(".heredoc");
		//free left & right
		if (right_cmnd != NULL)
			ft_pipes(global, --pipe_num, fd);
		else
			return (SUCCESS);
	}
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
		global->cmnd = line;
		init_list(&global->cmnd_list, line);
		ft_pipes(global, nbr_mots(global->cmnd, '|'), NULL);
		free(line);
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
