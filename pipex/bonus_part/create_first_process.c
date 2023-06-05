/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_first_process.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerkeni <mkerkeni@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 15:01:17 by mkerkeni          #+#    #+#             */
/*   Updated: 2023/05/19 09:47:40 by mkerkeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	get_input(t_var var, int **pfd, int *tmp_fd)
{
	char	*line;
	char	*limiter;

	limiter = ft_strjoin(var.av[2], "\n");
	close_pipes(var, pfd, -1);
	line = get_next_line(0);
	while (line)
	{
		if (!ft_strncmp(line, limiter, ft_strlen(limiter)))
		{
			if (!ft_strncmp(line, limiter, ft_strlen(line)))
			{
				free(line);
				free(limiter);
				if (close(tmp_fd[1]) == -1)
					ft_error(2, var.in_fd, var.out_fd);
				return ;
			}	
		}
		if (write(tmp_fd[1], line, ft_strlen(line)) == -1)
			ft_error(9, var.in_fd, var.out_fd);
		free(line);
		line = get_next_line(0);
	}
	free(limiter);
}

int	create_process_here_doc(t_var var, int **pfd)
{
	int		pid;
	int		tmp_fd[2];

	if (pipe(tmp_fd) == -1)
		ft_error(1, var.in_fd, var.out_fd);
	pid = fork();
	if (pid == -1)
		ft_error(0, var.in_fd, var.out_fd);
	if (pid == 0)
	{
		if (close(pfd[0][0]) == -1)
			ft_error(2, var.in_fd, var.out_fd);
		get_input(var, pfd, tmp_fd);
		dup2(tmp_fd[0], STDIN_FILENO);
		if (close(tmp_fd[0]) == -1)
			ft_error(2, var.in_fd, var.out_fd);
		dup2(pfd[0][1], STDOUT_FILENO);
		if (close(pfd[0][1]) == -1)
			ft_error(2, var.in_fd, var.out_fd);
		exec_cmd(var, 3);
		exit(EXIT_FAILURE);
	}
	if (close(tmp_fd[0]) == -1 || close(tmp_fd[1]) == -1)
		ft_error(2, var.in_fd, var.out_fd);
	return (pid);
}

int	create_process_infile(t_var var, int **pfd)
{
	int	pid;
	int	i;

	i = -1;
	pid = fork();
	if (pid == -1)
		ft_error(0, var.in_fd, var.out_fd);
	if (pid == 0)
	{
		dup2(var.in_fd, STDIN_FILENO);
		if (close(var.in_fd) == -1)
			ft_error(4, var.in_fd, var.out_fd);
		if (close(pfd[0][0]) == -1)
			ft_error(2, var.in_fd, var.out_fd);
		i = 0;
		while (++i < var.pipe_nb)
			if (close(pfd[i][0]) == -1 || close(pfd[i][1]) == -1)
				ft_error(2, var.in_fd, var.out_fd);
		dup2(pfd[0][1], STDOUT_FILENO);
		if (close(pfd[0][1]) == -1)
			ft_error(2, var.in_fd, var.out_fd);
		exec_cmd(var, 2);
	}
	return (pid);
}
