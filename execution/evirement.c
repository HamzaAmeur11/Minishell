/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   evirement.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hameur <hameur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 22:46:29 by hameur            #+#    #+#             */
/*   Updated: 2022/08/29 23:35:21 by hameur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"


int builtin_fct(char **cmnd, char **env)
{
	if (ft_strncmp(cmnd[0] , (char *)"cd", 2) == SUCCESS)
		return(ft_cd(cmnd, env), SUCCESS);
	if (ft_strncmp(cmnd[0] , (char *)"pwd", 3) == SUCCESS)
		return(ft_pwd(), SUCCESS);
	if (ft_strncmp(cmnd[0] , (char *)"env", 3) == SUCCESS)
		return(ft_env(env), SUCCESS);
	if (ft_strncmp(cmnd[0] , (char *)"echo", 4) == SUCCESS)
		return(ft_echo(cmnd, env), SUCCESS);
	if (ft_strncmp(cmnd[0] , (char *)"exit", 4) == SUCCESS)
		return (ft_exit(cmnd), SUCCESS);
	// if (ft_strncmp(cmnd[0] , (char *)"unset", 5) == SUCCESS)
	// 	return(ft_unset(cmnd), SUCCESS);
	// if (ft_strncmp(cmnd[0] , (char *)"export", 6) == SUCCESS)
	// 	return(ft_export(cmnd), SUCCESS);
	return (FAILDE);
}

char *remove_path(char* s)
{
	int i = 5;
	int j = 0;
	char *str;
	
	str = (char *)malloc(ft_strlen(s) - i + 1);
	while (s[i] != 0)
		str[j++] = s[i++];
	str[j] = 0;
	return (str);
}

char **find_paths(char **env)
{
	int i = 0;
	int j = 1;
	while (env[i] != NULL)
	{
		j = ft_strncmp(env[i], (char *)"PATH=", 4);
		if (j == 0)
			break;
		i++;
	}
	char *str = remove_path(env[i]);
	return (ft_split(str, ':'));
}


int other_fct(char **cmnd, char **env)
{
	char **paths = find_paths(env);
	char *path_cmnd;
	int i = 0;
	while (paths[i] != NULL)
	{
		path_cmnd = ft_strlcat(paths[i++], ft_strlcat((char *)"/", cmnd[0]));
		if (access(path_cmnd, F_OK) == SUCCESS)
		{
			if (execve(path_cmnd, cmnd, env) < 0)
				return(printf("PTH=%s\tcmnd1=%s\tcmnd2=%s\n", path_cmnd, cmnd[0], cmnd[1]), FAILDE);
			return (SUCCESS);
		}
	}
	return (FAILDE);
}

void ft_error(int i, char **cmnd)
{
	(void)cmnd;
	(void)i;
	exit(1);
}

int execute_cmnd(char **cmnd, char **env)
{
	if (builtin_fct(cmnd, env) != SUCCESS)
	{
		if (other_fct(cmnd, env) != SUCCESS)
			ft_error(1, cmnd);
	}
	return(ft_free(cmnd), SUCCESS);
}