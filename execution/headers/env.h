/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmeur <hmeur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 16:32:38 by hmeur            #+#    #+#             */
/*   Updated: 2022/09/12 17:02:29 by hmeur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef ENV_H

# define ENV_H

typedef struct t_envi
{
	char	**env;
	char	*env_x;
	char	*var_name;
	char	*var_value;
	struct t_envi	*next;
}	t_envi;

void    free_env(t_envi **env);
void	add_back(t_envi **envi, t_envi *new_node);
t_envi	*new_node(char *env_x);
t_envi	*init_envi(char **env);
void	add_place(t_envi **envi, t_envi *new_node, int i);
int		size_envi(t_envi *env);
void	delete_node_env(t_envi **env, int i);
char    *value_var(char *env);
char    *name_var(char *env);
void	add_front(t_envi **envi, t_envi *new_node);


#endif