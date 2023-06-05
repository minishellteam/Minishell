/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerkeni <mkerkeni@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 12:53:39 by mkerkeni          #+#    #+#             */
/*   Updated: 2023/05/19 10:53:24 by mkerkeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_error(int x, int in_fd, int out_fd)
{
	if (x == 0)
		perror("ERROR: failed to fork the process\n");
	else if (x == 1)
		perror("ERROR: failed to open the pipe\n");
	else if (x == 2)
		perror("ERROR: failed to close the pipe\n");
	else if (x == 3)
		perror("ERROR: failed to wait for the process to finish\n");
	else if (x == 4)
		perror("ERROR: failed to close the file\n");
	else if (x == 5)
		perror("ERROR: Failed to find the command path\n");
	else if (x == 6)
		perror("ERROR: Failed to get the commands");
	else if (x == 7)
		perror("ERROR: the execve function call failed");
	close(in_fd);
	close(out_fd);
	exit(EXIT_FAILURE);
}

static int	get_fd(char *path, int x)
{
	int	fd;

	if (x == 0)
		fd = open(path, O_RDONLY, 0777);
	else
		fd = open(path, O_CREAT | O_TRUNC | O_WRONLY, 0777);
	if (fd == -1)
	{
		perror("ERROR: failed to open the file\n");
		exit(EXIT_FAILURE);
	}
	return (fd);
}

static char	*get_path(char **env)
{
	char	*path;
	int		i;

	i = -1;
	path = NULL;
	while (env[++i])
	{
		if (ft_strnstr(env[i], "PATH=/Users", ft_strlen(env[i])))
		{
			path = env[i] + 5;
			break ;
		}
	}
	return (path);
}

static void	create_processes(t_var var)
{
	int	pfd[2];
	int	pid1;
	int	pid2;

	if (pipe(pfd) == -1)
		ft_error(1, var.in_fd, var.out_fd);
	pid1 = fork();
	if (pid1 == -1)
		ft_error(0, var.in_fd, var.out_fd);
	if (pid1 == 0)
		exec_first_cmd(var, pfd);
	pid2 = fork();
	if (pid2 == -1)
		ft_error(0, var.in_fd, var.out_fd);
	if (pid2 == 0)
		exec_second_cmd(var, pfd);
	if (close(pfd[1]) == -1)
		ft_error(2, var.in_fd, var.out_fd);
	if (close(pfd[0]) == -1)
		ft_error(2, var.in_fd, var.out_fd);
	if (waitpid(pid1, NULL, 0) == -1)
		ft_error(3, var.in_fd, var.out_fd);
	if (waitpid(pid2, NULL, 0) == -1)
		ft_error(3, var.in_fd, var.out_fd);
}

int	main(int ac, char **av, char **env)
{
	int		in_fd;
	int		out_fd;
	char	*path;
	t_var	var;

	if (ac != 5)
	{
		perror("ERROR: Wrong number of arguments !\n");
		exit(EXIT_FAILURE);
	}
	in_fd = get_fd(av[1], 0);
	out_fd = get_fd(av[4], 1);
	if (!av[2][0] || !av[3][0] || av[2][0] == ' ' || av[3][0] == ' ')
		ft_error(6, in_fd, out_fd);
	path = get_path(env);
	if (!path)
		ft_error(5, in_fd, out_fd);
	var.av = av;
	var.env = env;
	var.in_fd = in_fd;
	var.out_fd = out_fd;
	var.path = path;
	create_processes(var);
	return (0);
}
