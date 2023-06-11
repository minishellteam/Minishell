/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerkeni <mkerkeni@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 16:03:10 by mkerkeni          #+#    #+#             */
/*   Updated: 2023/06/11 11:12:08 by mkerkeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_line_to_history(t_data *cmd)
{
	int		y;
	int		i;

	y = 0;
	i = 0;
	cmd->line = ft_strjoin(cmd->line, "\n");
	if (cmd->history[HISTORY_SIZE - 1])
	{
		cmd->history[0] = NULL;
		free(cmd->history[0]);
		i = 0;
		while (++i < HISTORY_SIZE)
			cmd->history[i - 1] = cmd->history[i];
		y = HISTORY_SIZE - 1;
	}
	else
		while (cmd->history[y] && y < HISTORY_SIZE)
			y++;
	cmd->history[y] = ft_strdup(cmd->line);
	ft_putstr_fd(cmd->history[y], cmd->hist_fd);
}

static int	get_nb_of_rows(t_data *cmd)
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
		cmd->rows = rows;
		if (close(fd) == -1)
			handle_error("Error: Failed to close '.history.txt' file", 1);
		return (1);
	}
	return (0);
}

void	get_old_history(t_data *cmd)
{
	int		i;
	char	*line;

	i = -1;
	cmd->hist_fd = open(".history.txt", O_RDWR | O_APPEND, 0777);
	if (cmd->hist_fd == -1)
		handle_error("ERROR: Failed to open '.history' file", 1);
	if (get_nb_of_rows(cmd))
	{
		if (cmd->rows > HISTORY_SIZE)
			while (++i < cmd->rows - HISTORY_SIZE)
				get_next_line(cmd->hist_fd);
		i = -1;
		while (++i < HISTORY_SIZE)
			free(cmd->history[i]);
		init_history(cmd->history);
		i = -1;
		line = get_next_line(cmd->hist_fd);
		while (line && ++i < HISTORY_SIZE)
		{
			cmd->history[i] = ft_strdup(line);
			line = get_next_line(cmd->hist_fd);
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

void	clear_history_file(t_data *cmd)
{
	int	fd;

	fd = 0;
	if (get_nb_of_rows(cmd))
	{
		if (cmd->rows >= HISTORY_SIZE)
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
