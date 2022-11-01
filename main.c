/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hameur <hameur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 13:59:40 by megrisse          #+#    #+#             */
/*   Updated: 2022/11/01 18:05:38 by hameur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"
#include <sys/types.h>
#include <sys/wait.h>

//protect all malloc in your minishell

int	check_pipe(t_list *list, int t)
{
	t_list *temp;

	temp = list;
	while (t != 0 && temp->next != NULL)
	{
		if (temp->next->type == PIPE)
			t--;
		temp = temp->next;
	}
	if (t == 0 && temp->type == PIPE && temp->next == NULL)
		return (FAILDE);
	return (SUCCESS);
}

void init_parties(t_global *glb, t_list **left, t_list **right, int pipe_num)
{
	int total_pipes = nbr_mots(glb->cmnd, '|');
	if (check_pipe(glb->cmnd_list, total_pipes) == FAILDE)
		return ;
	char **str = ft_split(glb->cmnd, '|');
	if (str == NULL)
		return ;
	*left = init_list(glb, *left, str[total_pipes - pipe_num]);

	if (str[total_pipes - pipe_num + 1] != NULL)
		*right = init_list(glb, *right, str[total_pipes - pipe_num + 1]);
	else
		right = NULL;
	ft_free(str);
}




int close_fds(t_list *right, int *fd, int *old_fd, int key)
{
	if (key == 1)
	{
		if (old_fd != NULL)
		{
			close(old_fd[0]);
			close(old_fd[1]);
		}
	}
	else
	{
		if (old_fd != NULL)
		{
			dup2(old_fd[0], STDIN_FILENO);
			close(old_fd[0]);
			close(old_fd[1]);
		}
		if (right != NULL)
		{
			dup2(fd[1], STDOUT_FILENO);
			close(fd[0]);
			close(fd[1]);
		}
	}
	return (SUCCESS);
}

int exec_builting(t_list *cmnd_list, t_global *glb)
{
	t_cmnd	*cmnd;
	int		red_type = 0;
	int		old_fd = -1;
	int		red_back = -1;
	int		i = 0;

	cmnd = initializ_cmnd(cmnd_list, glb->env);
	red_type = type_red(cmnd_list);
	if (red_type == R_OUT || red_type == DR_OUT)
	{
		old_fd = redirection_out(name_red(cmnd_list), red_type);
		red_back = STDOUT_FILENO;
	}
	else if (red_type == R_INP || red_type == DR_INP)
	{
		old_fd = redirection_inp(name_red(cmnd_list), red_type);
		red_back = STDIN_FILENO;
	}
	if (builtin_fct(cmnd, glb) != SUCCESS)
		i = -1;
	if (red_type != 0)
		dup2(old_fd, red_back);
	free_tcmnd(cmnd);
	if (i == -1)
		return (FAILDE);
	return (SUCCESS);
}


int ft_pipes(t_global *global, int pipe_num, int *old_fd, int key)
{
	t_list *left_cmnd = NULL;
	t_list *right_cmnd = NULL;


	init_parties(global, &left_cmnd, &right_cmnd, pipe_num);
	if (left_cmnd == NULL)
		return (write(2, "Error Pipe\n", 11), FAILDE);
	global->status = exec_builting(global->cmnd_list, global);
	if (key == 0 && right_cmnd == NULL && global->status == SUCCESS)
		return (free_list(&left_cmnd, left_cmnd), SUCCESS);
	int	fd[2];
	if (pipe(fd) < 0)
		return (FAILDE);
	int	pid = fork();
	if (pid < 0)
		return (FAILDE);
	if (pid == 0)
	{
		close_fds(right_cmnd, fd, old_fd, 0);
		if (exec_cmnd(left_cmnd, global) != SUCCESS)
			return (FAILDE);
		return (free_list(&left_cmnd, left_cmnd), SUCCESS);
	}
	if (pid > 0)
	{
		close_fds(NULL, NULL, old_fd, 1);
		wait(&global->status);
		unlink(".heredoc");
		if (right_cmnd != NULL)
			ft_pipes(global, --pipe_num, fd, 1);
	}
	free_list(&left_cmnd, left_cmnd);
	if (right_cmnd != NULL)
		free_list(&right_cmnd, right_cmnd);
	return (0);
}


void print_l(t_list **head, char *str)
{
	t_list *temp = *head;
	printf("%s\n", str);
	while (temp != NULL)
	{
		printf("\t%s\n", temp->str);
		temp = temp->next;
	}
}

int shell(t_global *global)
{
	char *line;
	int	n_cmnd;
	int j;
	while(1337)
	{
		line = readline("Minishel => ");
		//fct for exit ctrl-D
		if (line == NULL)
			ft_exit(global, 1);
		j = ft_strlen(line);
		if (j != 0)
			add_history(line);
		if (j == 0)
			continue ;
		global->cmnd = line;
		global->cmnd_list = init_list(global, global->cmnd_list, line);
		if (global->cmnd_list == NULL)
			continue ;
		print_l(&global->cmnd_list, "cmnd_list");
		n_cmnd = nbr_mots(global->cmnd, '|');
		global->status = ft_pipes(global, n_cmnd, NULL, 0);
		free_list(&global->cmnd_list, global->cmnd_list);
		free(line);
	}
	return (SUCCESS);
}

int main(int ac, char **av, char **env)
{
	t_global *global;
	global = (t_global *)malloc(sizeof(t_global));
	global->env = init_envi(env);

	//env valide
	(void)ac;(void)av;
	handler_sig(global);
	shell(global);
	return (SUCCESS);
}