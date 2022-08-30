#include "mini.h"

void	ft_pwd()
{
	printf("%s\n", getcwd(NULL, 0));
}

void ft_env(char **env)
{
	int i = -1;

	while (env[++i] != NULL)
		printf("%s\n", env[i]);
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
}

void ft_exit(char **cmnd)
{
	ft_free(cmnd);
	exit(1);
}

int	ft_cd(char **cmnd, char **env)
{
	if (chdir(cmnd[1]) != 0)
		return(printf("errorf cd\n"),FAILDE);
	return (SUCCESS);
}