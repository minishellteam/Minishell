/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykifadji <ykifadji@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 14:33:20 by mkerkeni          #+#    #+#             */
/*   Updated: 2023/09/12 11:45:32 by ykifadji         ###   ########.fr       */
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

static void	get_std_stream(int fd, int std_stream)
{
	if (dup2(fd, std_stream) == -1)
	{
		perror("minishell: ");
		exit(EXIT_FAILURE);
	}
	if (close(fd) == -1)
	{
		perror("minishell: ");
		exit(EXIT_FAILURE);
	}
}

static int	create_only_process(t_vars *var, t_data *sh)
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
			get_std_stream(var->cmd[0].fdin, STDIN_FILENO);
		if (var->cmd[0].fdout != 1)
			get_std_stream(var->cmd[0].fdout, STDOUT_FILENO);
		if (exec_cmd(var, sh))
			exit(EXIT_FAILURE);
	}
	if (waitpid(pid, NULL, 0) == -1)
		perror("minishell: ");
	return (0);
}

int	create_processes(t_vars *var, t_data *sh)
{
	if (!var->pipe_nb)
	{
		if (create_only_process(var, sh))
			return (1);
	}
	//else
	//	create_multiple_processes(var);
	return (0);
}
