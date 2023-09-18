/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerkeni <mkerkeni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 14:33:20 by mkerkeni          #+#    #+#             */
/*   Updated: 2023/09/18 12:33:58 by mkerkeni         ###   ########.fr       */
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

void	get_std_stream(int fd, int std_stream)
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

static int	create_only_process(t_vars *var)
{
	int		pid;
	int		pfd[2];
	t_input	*tmp;

	tmp = var->data;
	pid = fork();
	printf("PID = %d\n", pid);
	if (pid == -1)
		perror("minishell: ");
	else if (pid)
		var->cmd->pid = pid;
	if (var->cmd[0].fdin == -2)
	{
		if (pipe(pfd) == -1)
			perror("minishell: ");
		if (close(pfd[0]) == -1)
			perror("minishell: ");
		while (tmp)
		{
			ft_putstr_fd(tmp->input, pfd[1]);
			tmp = tmp->next;
		}
		if (close(pfd[1]) == -1)
			perror("minishell: ");
	}
	if (pid == 0)
	{
		if (var->cmd[0].fdin != 0 && var->cmd[0].fdin != -2)
			get_std_stream(var->cmd[0].fdin, STDIN_FILENO);
		if (var->cmd[0].fdin == -2)
		{
			if (close(pfd[1]) == -1)
				perror("minishell : ");
			get_std_stream(pfd[0], STDIN_FILENO);
		}
		if (var->cmd[0].fdout != 1)
			get_std_stream(var->cmd[0].fdout, STDOUT_FILENO);
		if (exec_cmd(var))
			exit(EXIT_FAILURE);
	}
	if (waitpid(pid, NULL, 0) == -1)
		perror("minishell: ");
	return (0);
}

int	create_processes(t_vars *var, t_data *sh)
{
	var->orig_stdin = dup(STDIN_FILENO);
	var->orig_stdout = dup(STDOUT_FILENO);
	if (!var->pipe_nb)
	{
		if (var->cmd[0].args[0] && is_builtin(var->cmd[0].args[0]))
			handle_builtin(var, sh);
		else if (var->cmd[0].args[0] && !ft_strcmp(var->cmd[0].args[0], ""))
			get_error_message("", 4);
		//else if (var->cmd[0].args[0] && !ft_strcmp(var->cmd[0].args[0], ""))
		else
			if (create_only_process(var))
				return (1);
	}
	//else
	//	create_multiple_processes(var);
	return (0);
}
