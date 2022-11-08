/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_vars.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hameur <hameur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 16:01:47 by hmeur             #+#    #+#             */
/*   Updated: 2022/11/08 17:32:13 by hameur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

t_envi	*find_var(t_envi **env, char *name)
{
	t_envi	*temp;

	temp = *env;
	if (name == NULL)
		return (NULL);
	while (temp != NULL && temp->var_name != NULL)
	{
		printf("temp : %s\n", temp->var_name);
		if (ft_strncmp(temp->var_name, name, ft_strlen(name)) == 0)
			return (temp);
		temp = temp->next;
	}
	return (NULL);
}

int	change_var_value(t_envi *temp, char *name, char *value)
{
	printf("llllllllll\n");
	char *ptr = NULL;
	if (temp == NULL)
		return (FAILDE);
	free(temp->env_x);
	free(temp->var_name);
	free(temp->var_value);
	if (value != NULL)
	{
		temp->var_value = ft_strdup(value);
		ptr = ft_strlcat((char *)"=", value);
	}
	temp->env_x = ft_strlcat(name, ptr);
	temp->var_name = ft_strdup(name);
	if (temp->next == NULL)
		printf("zeeeebbbbbbbiiiiiiii\n");
	return (free(ptr), SUCCESS);
}

int	check_var(char *cmnd)
{
	int	i;

	i = 0;
	while (cmnd[i] != 0 && cmnd[i] != '=')
		i++;
	if (cmnd[i] == 0)
		return (FAILDE);
	return (SUCCESS);
}

void	print_expo(t_envi *env)
{
	while (env != NULL)
	{
		printf("declare -x %s\n", env->env_x);
		env = env->next;
	}
}

int	ft_export(t_cmnd *cmnd, t_envi **env)
{
	char 	*name;
	char 	*value;
	t_envi	*temp;
	int i = 1;

	if (cmnd->cmnd[1] == NULL)
		print_expo(*env);
	while (cmnd->cmnd[i])
	{
		// if (check_var(cmnd->cmnd[i]) != SUCCESS)
		// 	return (FAILDE);
		name =  name_var(cmnd->cmnd[i]);
		printf("name ----->%s\n", name);
		temp = find_var(env, name);
			printf("aaaaaaaa\n");
		if (temp != NULL)
		{
			value = value_var(cmnd->cmnd[i++]);
			change_var_value(temp, name, value);
			free(name);
			if (value != NULL)
				free(value);
			continue ;
		}
		add_back(env, new_node(cmnd->cmnd[i++]));
		free(name);
	}
	
	return (SUCCESS);
}

void unset_utils(t_envi *env, char *str)
{
	int i = 0;
	t_envi *temp = env;

	
	while (temp != NULL && i++ >= 0)
	{
		if (ft_strncmp(temp->var_name, str, ft_strlen(temp->var_name)) == SUCCESS)
		{
			delete_node_env(&env, i - 1);
			break ;
		}
		temp = temp->next;
	}
	
}

int ft_unset(t_cmnd *cmnd, t_envi **env)
{
	int j = 0;
	
	while (cmnd->cmnd[++j])
		unset_utils(*env, cmnd->cmnd[j]);
	return (SUCCESS);
}

