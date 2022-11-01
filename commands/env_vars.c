/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_vars.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hameur <hameur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 16:01:47 by hmeur             #+#    #+#             */
/*   Updated: 2022/11/01 21:33:53 by hameur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

t_envi	*find_var(t_envi *env, char *name)
{
	t_envi	*temp;

	temp = env;
	while (temp != NULL)
	{
		if (ft_strncmp(temp->var_name, name, ft_strlen(name)) == 0)
			return (temp);
		temp = temp->next;
	}
	return (NULL);
}

int	change_var_value(t_envi *env, char *name, char *value)
{
	t_envi	*temp;
	char *ptr;

	temp = find_var(env, name);
	if (temp == NULL)
		return (FAILDE);
	free(temp->env_x);
	ptr = ft_strlcat((char *)"=", value);
	temp->env_x = ft_strlcat(temp->var_name, ptr);
	temp->var_value = ft_strdup(value);
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

int	ft_export(t_cmnd *cmnd, t_envi **env)
{
	char *name;
	char *value;
	
	name =  name_var(cmnd->cmnd[1]);
	value = value_var(cmnd->cmnd[1]);
	if (check_var(cmnd->cmnd[1]) != SUCCESS)
		return (FAILDE);
	if (find_var(*env, name) != NULL)
	{
		change_var_value(*env, name, value);
		free(name);
		free(value);
		return (SUCCESS);
	}
	add_back(env, new_node(cmnd->cmnd[1]));
	return (free(name), SUCCESS);
}


int ft_unset(t_cmnd *cmnd, t_envi **env)
{
	t_envi *temp = *env;
	int i = 0;
	while (temp != NULL && i++ >= 0)
	{
		if (ft_strncmp(temp->env_x, cmnd->cmnd[1], ft_strlen(cmnd->cmnd[1] - 1)) == SUCCESS)
		{
			delete_node_env(env, i - 1);
			break ;
		}
		temp = temp->next;
	}
	return (SUCCESS);
}

