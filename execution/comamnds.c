#include "mini.h"

void	ft_pwd(char **cmnd)
{
	printf("%s\n", getcwd(NULL, 0));
	ft_free(cmnd);
	exit(0);
}

void ft_env(char **cmnd, char **env)
{
	int i = -1;

	while (env[++i] != NULL)
		printf("%s\n", env[i]);
	ft_free(cmnd);
	exit(0);
}

void ft_echo(char **cmnd, char **env)
{
	int i = 0;

	while (cmnd[++i] != NULL)
	{
		/*_______check variables________*/
		printf("%s ", cmnd[i]);
	}
	printf("\n");
	ft_free(cmnd);
	exit(0);
}

void ft_exit(char **cmnd)
{
	ft_free(cmnd);
	exit(1);
}

void	ft_cd(char **cmnd, char **env)
{
	if (chdir(cmnd[1]) != 0)
	{
		printf("errorf cd\n");
		ft_free(cmnd);
		exit(1);
	}
	ft_free(cmnd);
	exit(0);
}