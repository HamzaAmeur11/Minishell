/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmeur <hmeur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 22:44:38 by hameur            #+#    #+#             */
/*   Updated: 2022/09/21 19:51:40 by hmeur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL

#define MINISHELL

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "headers/env.h"
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

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






typedef struct t_global
{
	struct t_envi	*env;
	struct t_list	*cmnd_list;
	
}	t_global;

typedef struct t_list
{
	char	*str;
	int		type;
	struct t_list	*next;
}	t_list;

typedef struct t_cmnd
{
	char **cmnd;
	char **env;
}	t_cmnd;



int		ft_strlen(char *str);
int		ft_putstr_fd(int fd, char *str);
char	*ft_strdup(char *s1);
char	**ft_split(char *s, char c);
char	*ft_strlcat(char *s1, char *s2);
int		ft_strncmp(char *s1, char *s2, int i);
char	**find_paths(t_envi **env);
char	*remove_debut(char* s, int i);
int		other_fct(t_cmnd *cmnd, t_envi **env);
int 	execute_cmnd(char **cmnd, t_envi **env);

int		builtin_fct(t_cmnd *cmnd, t_envi **env);

void	ft_free(char **str);

void	ft_pwd(t_cmnd *cmnd, t_envi **env);
void	ft_exit(t_cmnd *cmnd, t_envi **env);
void	ft_cd(t_cmnd *cmnd, t_envi **env);
void 	ft_echo(t_cmnd *cmnd, t_envi **env);
void	ft_env(t_cmnd *cmnd, t_envi **env);
void	ft_export(t_cmnd *cmnd, t_envi **env);
void	ft_unset(t_cmnd *cmnd, t_envi **env);


void	free_list(t_list **root, t_list *node);
int		init_list(t_list **head, char *str);

//___________redirection_fcts______________
int		redirection_out(char *file_name, int red_type);
int		redirection_inp(char *file_name, int red_type);
char	*name_red(t_list *cmnd_list);
void	heredoc(char *file_name);
int		type_red(t_list *cmnd);




t_cmnd	*initializ_cmnd(t_global *global);
char	**init_env_table(t_envi *envi, int size);
char	**init_cmnd_table(t_list *cmnd, int size);


#endif	//MINISHELL