/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hameur <hameur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 20:23:51 by hmeur             #+#    #+#             */
/*   Updated: 2022/10/29 20:11:58 by hameur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"




char *get_var(t_envi **env, char *var_name)
{
	t_envi *temp;

	temp = *env;
	while (temp != NULL)
	{
		if (ft_strncmp(var_name, temp->var_name, 5) == SUCCESS)
			return (temp->var_value);
		temp = temp->next;
	}
	return (NULL);
}

void fttt_env(t_envi *env)
{
	while (env != NULL)
	{
		printf("env :  %s = %s\n", env->var_name, env->var_value);
		env = env->next;
	}
}

int	ft_cd(t_cmnd *cmnd, t_envi **env)
{
	char 	*old_pwd;
	char 	*o_pwd;
	char	pwd[1024];

	//fttt_env(*env);
	getcwd(pwd, 1024);
	old_pwd = ft_strdup(pwd);
	//check ~ option
	if (cmnd->cmnd[1] == NULL)
		return (chdir(get_var(env, "HOME")), SUCCESS);
	if (chdir(cmnd->cmnd[1]) != 0)
	{
		if (ft_strncmp(cmnd->cmnd[1] , "-", 1) == SUCCESS)
		{
			o_pwd = get_var(env, "OLDPWD");
			chdir(o_pwd);
			printf("~%s\n", o_pwd);
			return (free(o_pwd), SUCCESS);
		}
		printf("cd: no such file or directory: %s\n", cmnd->cmnd[1]);
		ft_free(cmnd->cmnd);
	}
	change_var_value(*env, "OLDPWD", old_pwd);
	change_var_value(*env, "PWD", pwd);
	return (SUCCESS);
}