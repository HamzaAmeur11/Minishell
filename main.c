/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hameur <hameur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 13:59:40 by megrisse          #+#    #+#             */
/*   Updated: 2022/11/10 22:58:30 by hameur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"
#include <sys/types.h>
#include <sys/wait.h>

//protect all malloc in your minishell

int	pipe_utils(t_global *glb, t_list *current, char **cmnd, int n_cmnd)
{
	int	i;

	i = 0;
	while (i < n_cmnd)
	{
		current = init_list(glb, current, cmnd[i], check_quotes(cmnd[i]));
		glb->p_in = glb->lastfd;
		if (cmnd[i + 1])
		{
			pipe(glb->fd);
			glb->p_out = glb->fd[1];
		}
		if (glb->pid > 0)
			glb->pid = fork();
		if (glb->pid < 0)
			return (ft_free(cmnd), ft_putstr_fd(2,
					"fork: Resource temporarily unavailable\n"), 1);
		if (glb->pid == 0)
			exec_child(glb, current);
		init_fds(glb, &i);
		free_list(&current, current);
		i++;
	}
	return (SUCCESS);
}

int	ft_pipes(t_global *glb, int n_cmnd)
{
	t_list	*current;
	char	**cmnd;
	int		i;

	current = NULL;
	glb->lastfd = -1;
	i = 0;
	glb->pid = 1;
	cmnd = ft_split(glb->cmnd, '|');
	if (n_cmnd == 1 && exec_onecmnd(glb, current, cmnd) == SUCCESS)
		return (ft_free(cmnd), SUCCESS);
	free_list(&current, current);
	if (pipe_utils(glb, current, cmnd, n_cmnd) == FAILDE)
		return (FAILDE);
	while (waitpid(-1, &glb->status, 0) > 0)
		;
	if (WIFEXITED(glb->status))
		glb->status = WEXITSTATUS(glb->status);
	else if (WIFSIGNALED(glb->status))
		glb->status = 128 + WTERMSIG(glb->status);
	close(glb->lastfd);
	return (ft_free(cmnd), SUCCESS);
}

int	shell(t_global *global)
{
	char	*line;
	int		n_cmnd;

	line = NULL;
	while (1337)
	{
		if (line != NULL)
			free(line);
		init_glb(global, &n_cmnd);
		line = readline("Minishel => ");
		if (line == NULL)
			ft_exit(global);
		if (ft_strlen(line) != 0)
			add_history(line);
		else
			continue ;
		if (init_and_check(global, line) == FAILDE)
			continue ;
		n_cmnd = nbr_mots(global->cmnd, '|', n_cmnd);
		global->status = ft_pipes(global, n_cmnd);
		unlink(".heredoc");
		free_list(&global->cmnd_list, global->cmnd_list);
	}
	return (SUCCESS);
}

int	main(int ac, char **av, char **env)
{
	t_global	*global;

	(void)ac;
	(void)av;
	global = (t_global *)malloc(sizeof(t_global));
	global->env = init_envi(env);
	handler_sig(global, 0);
	shell(global);
	return (SUCCESS);
}
