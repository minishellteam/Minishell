/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerkeni <mkerkeni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 14:49:54 by mkerkeni          #+#    #+#             */
/*   Updated: 2023/09/22 15:00:21 by mkerkeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	wait_for_processes(t_vars *var)
{
	int	i;

	i = -1;
	while (++i < var->pipe_nb + 1)
	{
		printf("pid[%d] = %d\n", i, var->cmd[i].pid);
		if (waitpid(var->cmd[i].pid, NULL, 0) == -1)
			return (-1);
	}
	return (0);
}

static void	set_stdin_pipeline(t_vars *var, int *pfd, int i)
{
	/*if (var->cmd[0].fdin == -2)
	{
		//if (close(pfd[0]) == -1)
		//	perror("minishell6");
		get_std_stream(fd de la pipe qui contient l'input here doc, STDIN_FILENO);
	}*/
	if (var->cmd[i].fdin != 0 && var->cmd[i].fdin != -2) // when there is an infile no matter if there is a pipe before
	{
		if (close(pfd[0]) == -1)
			perror("minishell7");
		get_std_stream(var->cmd[i].fdin, STDIN_FILENO);
	}
	else if (i && var->cmd[i].fdin == 0)// when there is no infile but a pipe before
		get_std_stream(pfd[0], STDIN_FILENO); 
	else // when there is no infile and no pipe before
		if (close(pfd[0]) == -1)
			perror("minishell12");
}

static void	set_stdout_pipeline(t_vars *var, int *pfd, int i)
{
	if (i < var->pipe_nb && var->cmd[i].fdout == 1) // when there is a pipe before
		get_std_stream(pfd[1], STDOUT_FILENO);
	else if (var->cmd[i].fdout != 1) // when there is an outfile
	{
		if (close(pfd[1]) == -1)
			perror("minishell14");
		get_std_stream(var->cmd[i].fdout, STDOUT_FILENO);
	}
	else // when there is no pipe after and no outfile
		if (close(pfd[1]) == -1)
			perror("minishell15");
}

static void	get_streams_pipeline(t_vars *var, int *pfd, int i)
{
	set_stdin_pipeline(var, pfd, i);
	set_stdout_pipeline(var, pfd, i);
}

void	create_multiple_processes(t_vars *var)
{
	int	pfd[2];
	int	*pids;
	int	i;

	i = -1;
	pids = malloc(sizeof(int) * (var->pipe_nb + 1));
	if (pipe(pfd) == -1)
		perror("minishell1");
	while (++i < var->pipe_nb + 1)
	{
		pids[i] = fork();
		if (pids[i] == -1)
			perror("minishell2");
		else if (pids[i])
			var->cmd[i].pid = pids[i];
		if (pids[i] == 0)
		{
			get_streams_pipeline(var, pfd, i);
			if (exec_cmd(var, i))
				exit(EXIT_FAILURE);
		}
		//dup2(var->orig_stdin, STDIN_FILENO);
		//dup2(var->orig_stdout, STDOUT_FILENO);
	}
	if (wait_for_processes(var) == -1)
		perror("minishell3");
	if (close(pfd[0]) == -1)
		perror("minishell4");
	if (close(pfd[1]) == -1)
		perror("minishell5");
	free(pids);
}
