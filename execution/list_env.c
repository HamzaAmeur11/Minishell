#include "mini.h"

t_envi *new_node(char **env, char *env_x, int x)
{
	t_envi *node;

	node = (t_envi *)malloc(sizeof(t_envi));
	if (!node)
		return (NULL);
	node->env = env;
	node->env_x = env_x;
	node->x = x;
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

t_envi *init_envi(char **env)
{
	t_envi *envi;
	int	i;

	i = -1;
	envi = NULL;
	while(env[++i] != NULL)
		add_back(&envi, new_node(env, env[i], i));
	return(envi);
}


