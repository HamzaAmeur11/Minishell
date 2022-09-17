#include "mini.h"
#include <sys/types.h>
#include <sys/wait.h>

//protect all malloc in your minishell




char **init_cmnd_table(t_list *cmnd, int size)
{
	char **comnd;
	t_list *temp = cmnd;
	int i = 0;
	comnd = (char **)malloc(sizeof(char *) * size);
	while (temp != NULL && temp->type == WORD)
	{
		comnd[i++] = temp->str;
		temp = temp->next;
	}
	comnd[i] = NULL;
	return (comnd);
}

char **init_env_table(t_envi *envi, int size)
{
	t_envi *temp = envi;
	char **env;
	env = (char **)malloc(sizeof(char *) * size);
	int i = 0;
	while (temp != NULL)
	{
		env[i++] = temp->env_x;
		temp = temp->next;
	}
	env[i] = NULL;
	return (env);
}

int type_red(t_list *cmnd)
{
	t_list *temp = cmnd;
	while (temp != NULL && temp->type == WORD)
		temp = temp->next;
	if (temp == NULL)
		return (FAILDE);
	return (temp->type);
}

t_cmnd *initializ_cmnd(t_global *global)
{
	t_cmnd *cmnd;
	t_list *temp = global->cmnd_list;
	int i = 0;
	cmnd = (t_cmnd *)malloc(sizeof(t_cmnd));
	
	while (temp != NULL && temp->type == WORD && i++ > -1)
		temp = temp->next;
	cmnd->cmnd = init_cmnd_table(global->cmnd_list, i + 1);
	cmnd->env = init_env_table(global->env, size_envi(global->env) + 1);
	return (cmnd);

}

void redirection(char *file_name, int red_type)
{
	int flags;
	int fd;

	if (red_type == R_OUT)
		flags = O_CREAT | O_RDWR | O_TRUNC;
	else if (red_type == DR_OUT)
		flags = O_CREAT | O_RDWR | O_APPEND;
	//ba9i inp & d_inp
	fd = open(file_name, flags, 0664);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	close(STDOUT_FILENO);
}

char *name_red(t_list *cmnd_list)
{
	t_list *temp = cmnd_list;

	while (temp != NULL && temp->type == WORD)
		temp = temp->next;
	return (temp->next->str);
}

int	exec_cmnd(t_global *global)
{
	t_cmnd *cmnd;
	char	*red;
	int		red_type;
	int		pid = fork();
	if (pid == 0)
	{
		cmnd = initializ_cmnd(global);
		red_type = type_red(global->cmnd_list);
		if (red_type > WORD)
			redirection(name_red(global->cmnd_list), red_type);
		if (builtin_fct(cmnd->cmnd, &global->env) != SUCCESS)
		{
			if (other_fct(cmnd->cmnd, &global->env) != SUCCESS)
				return (write(2 ,"error\n", 6), FAILDE);
		}
	}
	else
		wait(NULL);
}


int ff(t_global *global)
{
	char *line;
	char **cmnd;
	int id = 1;
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
		//free(line);
		//free_list(global->cmnd_list);
	}
	return (SUCCESS);
}

//builtin_fct (char **cmnd, t_env *env)
//other_fct (char **cmnd, t_envi *env)

int main(int ac, char **av, char **env)
{
	t_global *global;
	global = (t_global *)malloc(sizeof(t_global));
	global->env = init_envi(env);

	//env valide

	ff(global);
	return (SUCCESS);
}



/*int ff(t_global global)
{
	
	char *line;
	char **cmnd;
	int id = 1;
	while(1)
	{
		line = readline("Minishel => ");
		int j = ft_strlen(line);
		if (j != 0)
			add_history(line);
		if (j == 0)
			continue ;
		cmnd = ft_split(line, ' ');
		int i = builtin_fct(cmnd, global.env);
		if (id > 0 && i != SUCCESS)
			id = fork();
		if (id == 0)
		{
			if (other_fct(cmnd, global.env) != SUCCESS)
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
}*/