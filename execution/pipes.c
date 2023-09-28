/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerkeni <mkerkeni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 14:49:54 by mkerkeni          #+#    #+#             */
/*   Updated: 2023/09/28 14:53:09 by mkerkeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	set_stdin_pipeline(t_vars *var, int *pfd, int tmp_fd, int i)
{
	if (var->cmd[i].fdin == -2)
	{
		if (close(pfd[0]) == -1)
			perror("minishell6");
		get_std_stream(var->here_doc[0], STDIN_FILENO);
	}
	else if (var->cmd[i].fdin != 0)
	{
		if (close(pfd[0]) == -1)
			perror("minishell");
		get_std_stream(var->cmd[i].fdin, STDIN_FILENO);
	}
	else if (i && var->cmd[i].fdin == 0)
		get_std_stream(tmp_fd, STDIN_FILENO); 
	else
		if (close(pfd[0]) == -1)
			perror("minishell");
}

static void	set_stdout_pipeline(t_vars *var, int *pfd, int i)
{
	if (i < var->pipe_nb && var->cmd[i].fdout == 1)
		get_std_stream(pfd[1], STDOUT_FILENO);
	else if (var->cmd[i].fdout != 1)
	{
		if (close(pfd[1]) == -1)
			perror("minishell");
		get_std_stream(var->cmd[i].fdout, STDOUT_FILENO);
	}
	else
		if (close(pfd[1]) == -1)
			perror("minishell");
}

static void	close_pipes(t_vars *var, int *pfd, int i)
{
	if (i)
		if (close(var->tmp_fd) == -1)
			perror("minishell");
	if (var->cmd[i].fdin == -2)
		if (close(var->here_doc[0]) == -1)
			perror("minishell");
	if (close(pfd[1]) == -1)
		perror("minishell");
}

static void	handle_pipes(t_vars *var, int *pfd, int *pids, int i)
{
	while (++i < var->pipe_nb + 1)
	{
		if (var->cmd[i].fdin == -2)
		{
			if (pipe(var->here_doc) == -1)
				perror("minishell");
			get_here_doc_input(var, var->here_doc, i);
		}
		if (pipe(pfd) == -1)
			perror("minishell");
		pids[i] = fork();
		if (pids[i] == -1)
			perror("minishell");
		else if (pids[i])
			var->cmd[i].pid = pids[i];
		if (pids[i] == 0)
		{
			set_stdin_pipeline(var, pfd, var->tmp_fd, i);
			set_stdout_pipeline(var, pfd, i);
			if (exec_cmd(var, i))
				exit(EXIT_FAILURE);
		}
		close_pipes(var, pfd, i);
		var->tmp_fd = dup(pfd[0]);
	}
}

void	create_multiple_processes(t_vars *var)
{
	int	pfd[2];
	int	*pids;
	int	i;

	i = -1;
	pids = malloc(sizeof(int) * (var->pipe_nb + 1));
	handle_pipes(var, pfd, pids, i);
	if (wait_for_processes(var) == -1)
		perror("minishell");
	if (close(var->tmp_fd) == -1)
		perror("minishell");
	free(pids);
}
