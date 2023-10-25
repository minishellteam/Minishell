/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerkeni <mkerkeni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 14:02:10 by mkerkeni          #+#    #+#             */
/*   Updated: 2023/10/25 16:35:12 by mkerkeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	*get_exit_status(void)
{
	static int	exit_status;

	return (&exit_status);
}

void	set_exit_status(int status)
{
	*get_exit_status() = status;
}

void	wait_for_processes(t_vars *var)
{
	int	i;
	int	status;

	i = -1;
	while (++i < var->pipe_nb + 1)
	{
		if (waitpid(var->cmd[i].pid, &status, 0) == -1)
		{
			perror("minishell");
			return ;
		}
		if (WIFEXITED(status))
			set_exit_status(WEXITSTATUS(status));
		else if (WIFSIGNALED(status))
			set_exit_status(128 + WTERMSIG(status));
	}
	if (close(var->tmp_fd) == -1)
		perror("minishell");
}
