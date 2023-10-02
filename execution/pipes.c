/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerkeni <mkerkeni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 14:49:54 by mkerkeni          #+#    #+#             */
/*   Updated: 2023/09/21 12:13:18 by mkerkeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*static void	get_streams_pipeline(t_vars *var, int *pfd)
{
	// trouver les bons fd a dupliquer en fonction de si ya redirection ou non 
	//et si cmd redirigee vers pipe ou non
	//peut etre creer first process et last_process
	if (var->cmd[0].fdin == -2)
		get_std_stream(pfd[0], STDIN_FILENO);
	if (var->cmd[0].fdin != 0 && var->cmd[0].fdin != -2)
			get_std_stream(var->cmd[0].fdin, STDIN_FILENO);
	if (var->cmd[0].fdout != 1 && var->cmd[0].fdout != -2)
		get_std_stream(var->cmd[0].fdout, STDOUT_FILENO);
}

void	create_multiple_processes(t_vars *var)
{
	int	pfd[2];
	int	*pids;
	int	i;

	i = -1;
	pids = malloc(sizeof(int) * var->pipe_nb + 1);
	if (pipe(pfd) == -1)
		perror("minishell");
	while (++i < var->pipe_nb + 1)
	{
		pids[i] = fork();
		if (pids[i] == -1)
			perror("minishell");
		else if (pids[i])
			var->cmd[i].pid = pids[i];
		if (pids == 0)
		{
			get_streams(var, pfd);
			if (exec_cmd(var))
				exit(EXIT_FAILURE);
		}
	}
	free(pids);
}*/
