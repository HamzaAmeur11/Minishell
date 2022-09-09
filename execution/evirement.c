/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   evirement.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hameur <hameur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 22:46:29 by hameur            #+#    #+#             */
/*   Updated: 2022/08/31 00:29:52 by hameur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"


int builtin_fct(char **cmnd, t_envi **env)
{
	if (ft_strncmp(cmnd[0] , (char *)"cd", 2) == SUCCESS)
		return(ft_cd(cmnd, env), SUCCESS);
	if (ft_strncmp(cmnd[0] , (char *)"pwd", 3) == SUCCESS)
		return(ft_pwd(cmnd, env), SUCCESS);
	if (ft_strncmp(cmnd[0] , (char *)"env", 3) == SUCCESS)
		return(ft_env(cmnd, env), SUCCESS);
	if (ft_strncmp(cmnd[0] , (char *)"echo", 4) == SUCCESS)
		return(ft_echo(cmnd, env), SUCCESS);
	if (ft_strncmp(cmnd[0] , (char *)"exit", 4) == SUCCESS)
		return (ft_exit(cmnd, env), SUCCESS);
	 if (ft_strncmp(cmnd[0] , (char *)"unset", 5) == SUCCESS)
	 	return(ft_unset(cmnd, env), SUCCESS);
	 if (ft_strncmp(cmnd[0] , (char *)"export", 6) == SUCCESS)
	 	return(ft_export(cmnd, env), SUCCESS);
	return (FAILDE);
}

char *remove_debut(char* s, int i)
{
	int j = 0;
	char *str;
	
	str = (char *)malloc(ft_strlen(s) - i + 1);
	while (s[i] != 0)
		str[j++] = s[i++];
	str[j] = 0;
	return (str);
}

char **find_paths(t_envi **env)
{
	int i = 0;
	int j = 1;
	t_envi *temp = *env;
	char **paths;
	while (temp != NULL)
	{
		j = ft_strncmp(temp->env_x, (char *)"PATH=", 4);
		if (j == 0)
			break;
		temp = temp->next;
	}
	char *str = remove_debut(temp->env_x, 5);
	paths = ft_split(str, ':');
	return (free(str), paths);
}


int other_fct(char **cmnd, t_envi **env)
{
	char **paths = find_paths(env);
	char *path_cmnd;
	int i = 0;
	while (paths[i] != NULL)
	{
		path_cmnd = ft_strlcat(paths[i++], ft_strlcat((char *)"/", cmnd[0]));
		if (access(path_cmnd, F_OK) == SUCCESS)
		{
			if (execve(path_cmnd, cmnd, (*env)->env) < 0)
				return(printf("error f execve\n"), ft_free(paths), FAILDE);
			return (ft_free(paths), SUCCESS);
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

