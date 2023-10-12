/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerkeni <mkerkeni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 14:33:20 by mkerkeni          #+#    #+#             */
/*   Updated: 2023/10/09 15:45:41 by mkerkeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

static void	access_child_process(t_vars *var, int *pfd, int i)
{
	set_stdin_pipeline(var, pfd, var->tmp_fd, i);
	set_stdout_pipeline(var, pfd, i);
	if (is_builtin(var->cmd[i].args[0]))
	{
		var->sh->cmds = var->cmd[i].args;
		exec_builtin(var->sh);
		exit(*get_exit_status());
	}
	else if (exec_cmd(var, i))
		exit(*get_exit_status());
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
		{
			perror("minishell");
			exit(EXIT_FAILURE);
		}
		pids[i] = fork();
		if (pids[i] == -1)
			perror("minishell");
		else if (pids[i])
			var->cmd[i].pid = pids[i];
		if (pids[i] == 0)
			access_child_process(var, pfd, i);
		close_pipes(var, pfd, i);
		close_files(var, i);
		var->tmp_fd = dup(pfd[0]);
	}
}

int	create_processes(t_vars *var, t_data *sh)
{
	int	pfd[2];
	int	*pids;
	int	i;

	i = -1;
	pids = NULL;
	if (!var->pipe_nb && is_builtin(var->cmd[0].args[0]))
		handle_builtin(var, sh);
	else if (!var->pipe_nb && var->cmd[0].args[0]
		&& !ft_strcmp(var->cmd[0].args[0], ""))
		get_error_message("", 4);
	else
	{
		pids = (int *)ft_malloc(sizeof(int) * (var->pipe_nb + 1));
		handle_pipes(var, pfd, pids, i);
		if (wait_for_processes(var) == -1)
			perror("minishell");
		if (close(var->tmp_fd) == -1)
			perror("minishell");
		free(pids);
	}
	return (0);
}
