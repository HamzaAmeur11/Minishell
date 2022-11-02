/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hameur <hameur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 20:36:27 by hmeur             #+#    #+#             */
/*   Updated: 2022/11/02 20:41:26 by hameur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	ft_pwd(t_cmnd *cmnd, t_envi **env)
{
	t_envi	*temp;

	(void)cmnd;
	temp = find_var(*env, (char *)"PWD");
	printf("%s\n", temp->var_value);
	return (SUCCESS);
}

int	ft_env(t_cmnd *cmnd, t_envi **env)
{
	t_envi	*temp;

	(void)cmnd;
	temp = *env;
	while (temp != NULL)
	{
		printf("%s=%s\n", temp->var_name, temp->var_value);
		temp = temp->next;
	}
	return (SUCCESS);
}

int	print_var(char *var)
{
	if (var[0] == '$')
		return (SUCCESS);
	return (FAILDE);
}

char	*cherch_var(char *var, t_envi *env)
{
	int	i;

	while (env != NULL)
	{
		i = 0;
		while (var[i] != 0 && env->env_x[i] == var[i])
			i++;
		if (var[i] == 0)
			return (env->env_x + i + 1);
		env = env->next;
	}
	return ((char *)"");
}

int	ft_echo(t_cmnd *cmnd, t_envi **env)
{
	int	i;
	int	key;

	i = 0;
	key = 0;
	if (ft_strncmp(cmnd->cmnd[1], (char *)"-n", 2) == SUCCESS)
	{
		i++;
		key++;
	}
	while (cmnd->cmnd[++i] != NULL)
	{
		if (print_var(cmnd->cmnd[i]) == SUCCESS)
			printf("%s ", cherch_var(cmnd->cmnd[i] + 1, *env));
		else
			printf("%s ", cmnd->cmnd[i]);
	}
	if (key == 0)
		printf("\n");
	return (SUCCESS);
}

int	ft_exit(t_global *glb, int key)
{
	int	i;

	i = glb->status;
	free_env(&glb->env);
	free_list(&glb->cmnd_list, glb->cmnd_list);
	free(glb);
	if (key == 0)
		printf("exit\n");
	exit(i);
}
