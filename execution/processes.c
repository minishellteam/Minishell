/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerkeni <mkerkeni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 14:33:20 by mkerkeni          #+#    #+#             */
/*   Updated: 2023/10/02 09:38:06 by mkerkeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	get_std_stream(int fd, int std_stream)
{
	if (dup2(fd, std_stream) == -1)
	{
		perror("minishell20");
		exit(EXIT_FAILURE);
	}
	if (close(fd) == -1)
	{
		perror("minishell21");
		exit(EXIT_FAILURE);
	}
}

static void	get_streams(t_vars *var, int *pfd)
{
	if (var->cmd[0].fdin != 0 && var->cmd[0].fdin != -2)
		get_std_stream(var->cmd[0].fdin, STDIN_FILENO);
	else if (var->cmd[0].fdin == -2)
		get_std_stream(pfd[0], STDIN_FILENO);
	if (var->cmd[0].fdout != 1)
		get_std_stream(var->cmd[0].fdout, STDOUT_FILENO);
}

void	get_here_doc_input(t_vars *var, int *pfd, int i)
{
	t_input	*tmp;

	tmp = var->data[i];
	while (tmp)
	{
		ft_putstr_fd(tmp->input, pfd[1]);
		tmp = tmp->next;
	}
	if (close(pfd[1]) == -1)
		perror("minishell");
}

static int	create_only_process(t_vars *var)
{
	int		pid;
	int		pfd[2];

	if (var->cmd[0].fdin == -2)
	{
		if (pipe(pfd) == -1)
			perror("minishell");
		get_here_doc_input(var, pfd, 0);
	}
	pid = fork();
	if (pid == -1)
		perror("minishell");
	else if (pid)
		var->cmd[0].pid = pid;
	if (pid == 0)
	{
		get_streams(var, pfd);
		if (exec_cmd(var, 0))
			exit(*get_exit_status());
	}
	if (waitpid(pid, NULL, 0) == -1)
		perror("minishell");
	return (0);
}

int	create_processes(t_vars *var, t_data *sh)
{
	var->orig_stdin = dup(STDIN_FILENO);
	var->orig_stdout = dup(STDOUT_FILENO);
	var->sh = sh;
	if (!var->pipe_nb)
	{
		if (var->cmd[0].args[0] && is_builtin(var->cmd[0].args[0]))
			handle_builtin(var, sh);
		else if (var->cmd[0].args[0] && !ft_strcmp(var->cmd[0].args[0], ""))
			get_error_message("", 4);
		else
			if (create_only_process(var))
				return (1);
	}
	else
		create_multiple_processes(var);
	return (0);
}
