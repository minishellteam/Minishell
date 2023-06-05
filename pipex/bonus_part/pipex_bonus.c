/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerkeni <mkerkeni@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 12:53:39 by mkerkeni          #+#    #+#             */
/*   Updated: 2023/05/19 09:39:35 by mkerkeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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
		perror("ERROR: The execve function call failed");
	else if (x == 8)
		perror("ERROR: Failed to allocate memory for the pipes\n");
	else if (x == 9)
		perror("ERROR: Failed to write into the pipe\n");
	close(in_fd);
	close(out_fd);
	exit(EXIT_FAILURE);
}

void	close_pipes(t_var var, int **pfd, int i)
{
	int	j;

	j = -1;
	while (++j < var.pipe_nb)
	{
		if (j != i && j != i + 1)
		{
			if (close(pfd[j][0]) == -1)
				ft_error(2, var.in_fd, var.out_fd);
			if (close(pfd[j][1]) == -1)
				ft_error(2, var.in_fd, var.out_fd);
		}
	}
}

static int	get_fd(char *path, int x)
{
	int	fd;

	if (x == 0)
		fd = open(path, O_RDONLY, 0777);
	else
		fd = open(path, O_CREAT | O_WRONLY | O_APPEND, 0777);
	if (fd == -1)
	{
		perror("ERROR: failed to open the file\n");
		exit(EXIT_FAILURE);
	}
	return (fd);
}

static int	check_args(t_var var, int in_fd)
{
	int	i;

	i = 1;
	if (var.ac < 5)
	{
		perror("ERROR: Wrong number of arguments !\n");
		exit(EXIT_FAILURE);
	}
	if (!ft_strncmp(var.av[1], "here_doc", ft_strlen(var.av[1])))
	{
		i = 2;
		if (var.ac < 6)
		{
			perror("ERROR: Wrong number of arguments !\n");
			exit(EXIT_FAILURE);
		}
		var.pipe_nb = -1;
	}
	else
		in_fd = get_fd(var.av[1], 0);
	while (++i < var.ac - 1)
		if (!var.av[i][0] || var.av[i][0] == ' ')
			ft_error(6, var.in_fd, var.out_fd);
	return (in_fd);
}

int	main(int ac, char **av, char **env)
{
	int		in_fd;
	int		out_fd;
	char	*path;
	t_var	var;

	in_fd = 0;
	var.pipe_nb = 0;
	var.av = av;
	var.ac = ac;
	in_fd = check_args(var, in_fd);
	out_fd = get_fd(av[ac - 1], 1);
	path = get_path(env);
	if (!path)
		ft_error(5, in_fd, out_fd);
	var.env = env;
	var.in_fd = in_fd;
	var.out_fd = out_fd;
	var.path = path;
	var.pipe_nb += ac - 4;
	create_processes(var);
	return (EXIT_SUCCESS);
}
