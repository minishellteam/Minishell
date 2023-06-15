/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerkeni <mkerkeni@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 16:03:10 by mkerkeni          #+#    #+#             */
/*   Updated: 2023/06/15 11:42:14 by mkerkeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_line_to_history(void)
{
	int		y;
	int		i;

	y = 0;
	i = 0;
	g_sh.line = ft_strjoin(g_sh.line, "\n");
	if (g_sh.history[HISTORY_SIZE - 1])
	{
		g_sh.history[0] = NULL;
		free(g_sh.history[0]);
		i = 0;
		while (++i < HISTORY_SIZE)
			g_sh.history[i - 1] = g_sh.history[i];
		y = HISTORY_SIZE - 1;
	}
	else
		while (g_sh.history[y] && y < HISTORY_SIZE)
			y++;
	g_sh.history[y] = ft_strdup(g_sh.line);
	ft_putstr_fd(g_sh.history[y], g_sh.hist_fd);
}

static int	get_nb_of_rows(void)
{
	int		fd;
	char	*line;
	int		rows;

	rows = 0;
	fd = open(".history.txt", O_RDONLY, 0777);
	if (fd == -1)
		handle_error("ERROR: Failed to open '.history' file", 1);
	line = get_next_line(fd);
	if (line)
	{
		while (line)
		{
			rows++;
			free(line);
			line = get_next_line(fd);
		}
		g_sh.rows = rows;
		if (close(fd) == -1)
			handle_error("Error: Failed to close '.history.txt' file", 1);
		return (1);
	}
	return (0);
}

void	get_old_history(void)
{
	int		i;
	char	*line;

	i = -1;
	g_sh.hist_fd = open(".history.txt", O_RDWR | O_APPEND, 0777);
	if (g_sh.hist_fd == -1)
		handle_error("ERROR: Failed to open '.history' file", 1);
	if (get_nb_of_rows())
	{
		if (g_sh.rows > HISTORY_SIZE)
			while (++i < g_sh.rows - HISTORY_SIZE)
				get_next_line(g_sh.hist_fd);
		i = -1;
		while (++i < HISTORY_SIZE)
			free(g_sh.history[i]);
		init_history(g_sh.history);
		i = -1;
		line = get_next_line(g_sh.hist_fd);
		while (line && ++i < HISTORY_SIZE)
		{
			g_sh.history[i] = ft_strdup(line);
			line = get_next_line(g_sh.hist_fd);
		}
	}
}

void	init_history(char **history)
{
	int	i;

	i = -1;
	while (++i < HISTORY_SIZE)
		history[i] = NULL;
}

void	clear_history_file(void)
{
	int	fd;

	fd = 0;
	if (get_nb_of_rows())
	{
		if (g_sh.rows >= HISTORY_SIZE)
		{
			fd = open(".history.txt", O_WRONLY | O_TRUNC, 0777);
			if (fd == -1)
				handle_error("ERROR: Failed to open '.history' file", 1);
			if (write(fd, "", 0) == -1)
				handle_error("ERROR: Failed to write in '.history' file", 1);
			if (close(fd) == -1)
				handle_error("ERROR: Failed to close '.history' file", 1);
		}
	}
}
