/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_redirections.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerkeni <mkerkeni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 14:49:54 by mkerkeni          #+#    #+#             */
/*   Updated: 2023/10/27 00:28:26 by mkerkeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	get_std_stream(int fd, int std_stream)
{
	if (dup2(fd, std_stream) == -1)
	{
		perror("minishell");
		set_exit_status(1);
		exit(*get_exit_status());
	}
	if (close(fd) == -1)
	{
		perror("minishell");
		set_exit_status(1);
		exit(*get_exit_status());
	}
}

void	set_stdin_pipeline(t_vars *var, int *pfd, int tmp_fd, int i)
{
	if (var->cmd[i].fdin == -2)
	{
		if (close(pfd[0]) == -1)
			perror("minishell");
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

void	set_stdout_pipeline(t_vars *var, int *pfd, int i)
{
	if (i < var->pipe_nb && var->cmd[i].fdout == 1)
		get_std_stream(pfd[1], STDOUT_FILENO);
	else if (var->cmd[i].fdout != 1)
	{
		if (close(pfd[1]) == -1)
			perror("minishell");
		get_std_stream(var->cmd[i].fdout, STDOUT_FILENO);
		var->empty_pipe = 1;
	}
	else
		if (close(pfd[1]) == -1)
			perror("minishell");
}

void	close_files(t_vars *var, int i)
{
	if (var->cmd[i].fdin != 0 && var->cmd[i].fdin != -2)
		if (close(var->cmd[i].fdin) == -1)
			perror("minishell");
	if (var->cmd[i].fdout != 1)
		if (close(var->cmd[i].fdout) == -1)
			perror("minishell");
}

void	set_null_stdin(void)
{
	int		null_fd;

	null_fd = open("/dev/null", O_RDONLY);
	dup2(null_fd, STDIN_FILENO);
	close(null_fd);
}
