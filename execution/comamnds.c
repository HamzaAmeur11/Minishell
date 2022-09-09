#include "mini.h"

void	ft_pwd(char **cmnd, t_envi **env)
{
	printf("%s\n", getcwd(NULL, 0));
	ft_free(cmnd);
}

void ft_env(char **cmnd, t_envi **env)
{
	t_envi *temp = *env;

	while (temp != NULL)
	{
		printf("%s=%s\n", temp->var_name, temp->var_value);
		temp = temp->next;
	}
	ft_free(cmnd);
}

int print_var(char *var)
{
	if (var[0] == '$')
		return (SUCCESS);
	return (FAILDE);
}

char *cherch_var(char *var, t_envi *env)
{
	int i;
	while (env != NULL)
	{
		i = 0;
		while (var[i] != 0 && env->env_x[i] == var[i])
			i++;
		if (var[i] == 0)
			return (env->env_x + i + 1);
		env = env->next;
	}
	return (NULL);
}

void ft_echo(char **cmnd, t_envi **env)
{
	int i = 0;
	char *var;
	//check_using_echo without flage
	while (cmnd[++i] != NULL)
	{
		/*_______check variables________*/
		if (print_var(cmnd[i]) == SUCCESS)
			printf("%s ", cherch_var(cmnd[i] + 1, *env));
		else
			printf("%s ", cmnd[i]);
	}
	printf("\n");
	ft_free(cmnd);
}

void ft_exit(char **cmnd, t_envi **env)
{
	ft_free(cmnd);
	printf("exit\n");
	//check_exit_value//
	exit(1);
}

void	ft_cd(char **cmnd, t_envi **env)
{
	//check_using cd without flage
	if (chdir(cmnd[1]) != 0)
	{
		printf("cd: no such file or directory: %s\n", cmnd[1]);
		ft_free(cmnd);
	}
	ft_free(cmnd);
}

int check_var(char *cmnd)
{
	int i = 0;
	while (cmnd[i] != 0 && cmnd[i] != '=')
		i++;
	if (cmnd[i] == 0)
		return (FAILDE);
	return (SUCCESS);
}

void ft_export(char **cmnd, t_envi **env)
{
	int i = size_envi(*env);
	if (check_var(cmnd[1]) != SUCCESS)
		return ;
	add_place(env, new_node((*env)->env, cmnd[1]), i - 1);
}


void ft_unset(char **cmnd, t_envi **env)
{
	t_envi *temp = *env;
	int i = 0;
	while (temp != NULL && i++ >= 0)
	{
		if (ft_strncmp(temp->env_x, cmnd[1], ft_strlen(cmnd[1] - 1)) == SUCCESS)
		{
			delete_node_env(env, i - 1);
			break ;
		}
		temp = temp->next;
	}
}