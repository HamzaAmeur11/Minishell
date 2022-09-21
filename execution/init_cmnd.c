/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmnd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmeur <hmeur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 19:48:42 by hmeur             #+#    #+#             */
/*   Updated: 2022/09/21 19:50:44 by hmeur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

char **init_cmnd_table(t_list *cmnd, int size)
{
	char **comnd;
	t_list *temp = cmnd;
	int i = 0;
	comnd = (char **)malloc(sizeof(char *) * size);

	if (temp->type != WORD)
		temp = temp->next->next;
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


t_cmnd *initializ_cmnd(t_global *global)
{
	t_cmnd *cmnd;
	t_list *temp = global->cmnd_list;
	int i = 0;
	cmnd = (t_cmnd *)malloc(sizeof(t_cmnd));
	
	if (temp->type != WORD)
		temp = temp->next->next;
	while (temp != NULL && temp->type == WORD && i++ > -1)
		temp = temp->next;
	cmnd->cmnd = init_cmnd_table(global->cmnd_list, i + 1);
	cmnd->env = init_env_table(global->env, size_envi(global->env) + 1);
	return (cmnd);

}
