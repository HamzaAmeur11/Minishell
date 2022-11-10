/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hameur <hameur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 13:59:40 by megrisse          #+#    #+#             */
/*   Updated: 2022/11/10 19:38:49 by hameur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"
#include <sys/types.h>
#include <sys/wait.h>

//protect all malloc in your minishell

void	red_built(t_list *cmnd_list, int *red_type, int *old_fd, int *red_back)
{
	*red_type = type_red(cmnd_list);
	if (*red_type == R_OUT || *red_type == DR_OUT)
	{
		*old_fd = redirection_out(name_red(cmnd_list), *red_type);
		*red_back = STDOUT_FILENO;
	}
	else if (*red_type == R_INP || *red_type == DR_INP)
	{
		*old_fd = redirection_inp(name_red(cmnd_list), *red_type);
		*red_back = STDIN_FILENO;
	}
}

int	exec_builting(t_list *cmnd_list, t_global *glb)
{
	t_cmnd	*cmnd;
	int		red_type;
	int		old_fd;
	int		red_back;
	int		i;

	red_type = 0;
	old_fd = -1;
	red_back = -1;
	i = 0;
	cmnd = initializ_cmnd(cmnd_list, glb->env);
	red_built(cmnd_list, &red_type, &old_fd, &red_back);
	if (cmnd->cmnd[0] != NULL)
	{	
		if (builtin_fct(cmnd, glb) != SUCCESS)
			i = -1;
	}
	if (red_type != 0)
		dup2(old_fd, red_back);
	free_tcmnd(cmnd);
	if (i == -1)
		return (FAILDE);
	return (SUCCESS);
}

int	exec_onecmnd(t_global *glb, t_list *current, char **cmnd)
{
	current = init_list(glb, current, cmnd[0], check_quotes(cmnd[0]));
	if (exec_builting(current, glb) == SUCCESS)
		return (free_list(&current, current), ft_free(cmnd), SUCCESS);
	return (FAILDE);
}
			
int	ft_pipes(t_global *glb, int n_cmnd)
{
	t_list	*current = NULL;
	char	**cmnd;
	int		i;
	int		pid = 1;
	
	glb->lastfd = -1;
	i = 0;
	cmnd = ft_split(glb->cmnd, '|');
	if (n_cmnd == 1 && exec_onecmnd(glb, current, cmnd) == SUCCESS)
		return (SUCCESS);
	free_list(&current, current);
	while (i < n_cmnd)
	{
		current = init_list(glb, current, cmnd[i], check_quotes(cmnd[i]));
		glb->p_in = glb->lastfd;
		if (cmnd[i + 1])
		{
			if (pipe(glb->fd) != SUCCESS)
				return (FAILDE);
			glb->p_out = glb->fd[1];
		}
		if (pid > 0)
			pid = fork();
		if (pid < 0)
			return (ft_free(cmnd), ft_putstr_fd(2, "fork: Resource temporarily unavailable\n"), 1);
		if (pid == 0)
		{
			handler_sig(glb, 1);
			dup2(glb->p_in, STDIN_FILENO);
			close(glb->p_in);
			dup2(glb->p_out, STDOUT_FILENO);
			close(glb->p_out);
			close(glb->fd[0]);
			exec_cmnd(current, glb);
		}
		close(glb->fd[1]);
		close(glb->p_in);
		i++;
		glb->lastfd = glb->fd[0];
		glb->fd[0] = -1;
		glb->fd[1] = -1;
		glb->p_out = -1;
		free_list(&current, current);
	}
	while (waitpid(-1, &glb->status, 0) > 0);
	if (WIFEXITED(glb->status))
		glb->status = WEXITSTATUS(glb->status);
	else if (WIFSIGNALED(glb->status))	
		glb->status = 128 + WTERMSIG(glb->status);
	close(glb->lastfd);
	return (ft_free(cmnd), SUCCESS);
}

int check_red_name(char *str)
{
	int i = 0;
	char c = str[i];
	while (str[i] != 0 && str[i] == c && i < 2)
		i++;
	if (str[i] == 0 || str[i] == '>' || str[i] == '<' || str[i] == '|')
		return (FAILDE);
	return (SUCCESS);
}

int check_pipe(char *str, int key)
{
	int i = 0;
	while (str[i] != 0 && str[i] != '|')
		i++;
	if (key == 0 && i > 0 && str[i - 1] != '|')
		return (SUCCESS);
	else if (key == 1 && str[i] != 0 && str[i + 1] != 0 && str[i + 1] != '|')
		return (SUCCESS);
	return (FAILDE);
}

int check_syntax(t_list **list)
{
	int prev = -1;
	t_list *cmnd = *list;
	if (cmnd == NULL)
		return (FAILDE);
	while (cmnd != NULL)
	{
		if (cmnd->type == PIPE && ((prev == -1 && check_pipe(cmnd->str, 0) == FAILDE)|| (cmnd->next == NULL && check_pipe(cmnd->str, 1) == FAILDE)))
			return (free_list(list, *list), ft_putstr_fd(2, "syntax error near unexpected token `|'\n"), FAILDE);
		if (cmnd->type == PIPE)
			prev = -1;
		if (cmnd->type != WORD && cmnd->type != PIPE && check_red_name(cmnd->str) == FAILDE && cmnd->next == NULL)
			return (free_list(list, *list), ft_putstr_fd(2, "syntax error near unexpected token `newline'\n"), FAILDE);
		if (cmnd->type != PIPE && cmnd->next != NULL && cmnd->next->type == PIPE)
			prev = 0;
		cmnd = cmnd->next;
	}
	return (SUCCESS);
}

int shell(t_global *global)
{
	char *line = NULL;
	int	n_cmnd;

	while(42)
	{
		n_cmnd = 0;
		if (line != NULL)
			free(line);
		global->p_in = -1;
		global->p_out = -1;
		line = readline("Minishel => ");
		if (line == NULL)
			ft_exit(global);
		if (ft_strlen(line) != 0)
			add_history(line);
		else
			continue ;
		global->cmnd = line;
		global->cmnd_list = init_list(global, global->cmnd_list, line, 0);
		if (check_syntax(&global->cmnd_list) != SUCCESS)
			continue ;
		n_cmnd = nbr_mots(global->cmnd, '|', n_cmnd);
		global->status = ft_pipes(global, n_cmnd);
		unlink(".heredoc");
		free_list(&global->cmnd_list, global->cmnd_list);
	}
	return (SUCCESS);
}

int main(int ac, char **av, char **env)
{
	t_global *global;
	(void)ac;
	(void)av;
	
	global = (t_global *)malloc(sizeof(t_global));
	global->env = init_envi(env);
	handler_sig(global, 0);
	shell(global);
	return (SUCCESS);
}
