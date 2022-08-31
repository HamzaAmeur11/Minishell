/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hameur <hameur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 22:44:38 by hameur            #+#    #+#             */
/*   Updated: 2022/08/31 00:15:51 by hameur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHEL

#define MINISHEL

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>


# define SUCCESS 0
# define FAILDE 1


# define WORD 10
# define PIPE 11
# define DQUOTE 12
# define SQUOTE 13
# define VAR 14
# define R_INP 15
# define R_OUT 16
# define DR_INP 17
# define DR_OUT 18





typedef struct t_envi
{
	char	**env;
	char	*env_x;
	int		x;
	struct t_envi	*next;
}	t_envi;

typedef struct t_list
{
	char	*split_cmnd;
	int		type;
	char	**cmnd;
	struct t_envi	*env;
	struct t_list	*next;	
}	t_list;

char	**ft_split(char *s, char c);
char	**find_paths(char **env);
char	*remove_path(char* s);
char	*ft_strlcat(char *s1, char *s2);
int		ft_strncmp(char *s1, char *s2, int i);
int		other_fct(char **cmnd, char **env);
int		ft_strlen(char *str);
void	ft_pwd(char **cmnd);
int 	execute_cmnd(char **cmnd, char **env);
void	ft_env(char **cmnd, char **env);
void 	ft_echo(char **cmnd, char **env);
void	ft_free(char **str);
void	ft_exit(char **cmnd);
void	ft_cd(char **cmnd, char **env);
void	add_back(t_envi **envi, t_envi *new_node);
t_envi	*new_node(char **env, char *env_x, int x);
t_envi	*init_envi(char **env);



#endif