#include "mini.h"


char *name_var(char *env)
{
	int		i;
	int		j;
	char	*name = NULL;

	j = -1;
	i = 0;
	while(env[i] != 0 && env[i] != '=')
		i++;
	name = malloc(i + 1);
	while (env[++j] != '=')
		name[j] = env[j];
	name[j] = 0;
	return (name);
}

char *value_var(char *env)
{
	int i;

	i = 0;
	while(env[i] != 0 && env[i] != '=')
		i++;
	return (env + i + 1);
}

t_envi *new_node(char **env, char *env_x)
{
	t_envi *node;

	node = (t_envi *)malloc(sizeof(t_envi));
	if (!node)
		return (NULL);
	node->env = env;
	node->env_x = env_x;
	node->var_name = name_var(env_x);
	node->var_value = value_var(env_x);
	node->next = NULL;
	return (node);
}

void add_back(t_envi **envi, t_envi *new_node)
{
	t_envi *temp;
	
	temp = *envi;
	if (temp == NULL)
	{
		*envi = new_node;
		return ;
	}
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = new_node;
	new_node->next = NULL;
}

int	size_envi(t_envi *env)
{
	t_envi *temp = env;
	int i = 0;

	while (temp != NULL && i++ >= 0)
		temp = temp->next;
	return(i);
}

void add_place(t_envi **envi, t_envi *new_node, int i)
{
	t_envi *temp = *envi;
	int size = size_envi(*envi);
	temp = *envi; 
	while (temp->next->next != NULL && i < size)
		temp = temp->next;
	new_node->next = temp->next;
	temp->next = new_node;
}

void delete_node_env(t_envi **env, int i)
{
	t_envi *temp = *env;
	while (temp != NULL && i-- > 1)
		temp = temp->next;
	if (temp == NULL)
		return ;
	t_envi *ptr = temp->next;
	temp->next = ptr->next;
	free(ptr);
}

t_envi *init_envi(char **env)
{
	t_envi *envi;
	int	i;

	i = -1;
	envi = NULL;
	while(env[++i] != NULL)
		add_back(&envi, new_node(env, env[i]));
	return(envi);
}


