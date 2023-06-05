/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerkeni <mkerkeni@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 15:35:55 by mkerkeni          #+#    #+#             */
/*   Updated: 2023/05/18 11:54:35 by mkerkeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	free_str(char **str)
{
	int	i;

	i = -1;
	while (str[++i])
		free(str[i]);
}

static char	**get_commands(t_var var, int x)
{
	char	**cmds;

	if (x == 0)
		cmds = ft_split(var.av[2], ' ');
	else
		cmds = ft_split(var.av[3], ' ');
	if (!cmds)
		ft_error(6, var.in_fd, var.out_fd);
	return (cmds);
}

static char	*get_cmd_path(t_var var, char **cmds)
{
	char	**splitted_paths;
	char	*cmd_path;
	char	*test_cmd_path;
	int		i;

	i = -1;
	splitted_paths = ft_split(var.path, ':');
	while (splitted_paths[++i])
	{
		test_cmd_path = ft_strjoin(splitted_paths[i], "/");
		cmd_path = ft_strjoin(test_cmd_path, cmds[0]);
		free(test_cmd_path);
		if (access(cmd_path, X_OK) == 0)
		{
			free_str(splitted_paths);
			return (cmd_path);
		}
	}
	free(cmd_path);
	free(splitted_paths);
	return (NULL);
}

void	exec_first_cmd(t_var var, int *pfd)
{
	char	**cmds1;
	char	*cmd_path;

	dup2(var.in_fd, STDIN_FILENO);
	if (close(var.in_fd) == -1)
		ft_error(4, var.in_fd, var.out_fd);
	if (close(pfd[0]) == -1)
		ft_error(2, var.in_fd, var.out_fd);
	dup2(pfd[1], STDOUT_FILENO);
	if (close(pfd[1]) == -1)
		ft_error(2, var.in_fd, var.out_fd);
	cmds1 = get_commands(var, 0);
	if (cmds1[0][0] != '/')
	{
		cmd_path = get_cmd_path(var, cmds1);
		if (!cmd_path)
		{
			free_str(cmds1);
			ft_error(5, var.in_fd, var.out_fd);
		}
		cmds1[0] = cmd_path;
	}
	if (execve(cmds1[0], cmds1, var.env) == -1)
		ft_error(7, var.in_fd, var.out_fd);
}

void	exec_second_cmd(t_var var, int *pfd)
{
	char	**cmds2;
	char	*cmd_path;

	dup2(var.out_fd, STDOUT_FILENO);
	if (close(var.out_fd) == -1)
		ft_error(4, var.in_fd, var.out_fd);
	if (close(pfd[1]) == -1)
		ft_error(2, var.in_fd, var.out_fd);
	dup2(pfd[0], STDIN_FILENO);
	if (close(pfd[0]) == -1)
		ft_error(2, var.in_fd, var.out_fd);
	cmds2 = get_commands(var, 1);
	if (cmds2[0][0] != '/')
	{
		cmd_path = get_cmd_path(var, cmds2);
		if (!cmd_path)
		{
			free_str(cmds2);
			ft_error(5, var.in_fd, var.out_fd);
		}
		cmds2[0] = cmd_path;
	}
	if (execve(cmds2[0], cmds2, var.env) == -1)
		ft_error(7, var.in_fd, var.out_fd);
}
