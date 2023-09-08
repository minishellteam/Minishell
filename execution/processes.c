/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerkeni <mkerkeni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 14:33:20 by mkerkeni          #+#    #+#             */
/*   Updated: 2023/09/08 14:22:11 by mkerkeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*void	create_multiple_processes(t_vars *var)
{
	int	**pfd;
	int	first_pid;
	int	last_pid;
	int	*mid_pids;

	mid_pids = malloc(sizeof(int) * (var.pipe_nb - 1));
	pfd = get_pfd(var);
	if (!var.in_fd)
		first_pid = create_process_here_doc(var, pfd);
	else
		first_pid = create_process_infile(var, pfd);
	if (var.pipe_nb > 1)
		mid_pids = create_mid_processes(var, pfd, mid_pids);
	last_pid = create_last_process(var, pfd);
	close_pipes(var, pfd, -2);
	wait_for_processes(var, first_pid, last_pid, mid_pids, 0);
	if (var.pipe_nb > 1)
		wait_for_processes(var, first_pid, last_pid, mid_pids, 1);
	wait_for_processes(var, first_pid, last_pid, mid_pids, 2);
	free_array(pfd, var.pipe_nb);
	free(mid_pids);
}*/

static int	create_only_process(t_vars *var)
{
	int	pid;

	pid = fork();
	printf("PID = %d\n", pid);
	if (pid == -1)
		perror("minishell: ");
	else if (pid)
		var->cmd->pid = pid;
	else if (pid == 0)
	{
		if (var->cmd[0].fdin != 0)
		{
			if (dup2(var->cmd[0].fdin, STDIN_FILENO) == -1)
				perror("minishell: ");
			if (close(var->cmd[0].fdin) == -1)
				perror("minishell: ");
		}
		if (var->cmd[0].fdout != 1)
		{
			if (dup2(var->cmd[0].fdout, STDOUT_FILENO) == -1)
				perror("minishell: ");
			if (close(var->cmd[0].fdout) == -1)
				perror("minishell: ");
		}
		if (exec_cmd(var))
			exit(EXIT_FAILURE);
	}
	if (waitpid(pid, NULL, 0) == -1)
		perror("minishell: ");
	return (0);
}

int	create_processes(t_vars *var)
{
	if (!var->pipe_nb)
	{
		if (create_only_process(var))
			return (1);
	}
	//else
	//	create_multiple_processes(var);
	return (0);
}
