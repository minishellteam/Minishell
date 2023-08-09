/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerkeni <mkerkeni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 16:03:10 by mkerkeni          #+#    #+#             */
/*   Updated: 2023/08/09 14:41:27 by mkerkeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_line_to_history(char *line, char **history, int hist_fd)
{
	int		y;
	int		i;

	y = 0;
	i = 0;
	line = ft_strjoin(line, "\n");
	if (history[HISTORY_SIZE - 1])
	{
		history[0] = NULL;
		free(history[0]);
		i = 0;
		while (++i < HISTORY_SIZE)
			history[i - 1] = history[i];
		y = HISTORY_SIZE - 1;
	}
	else
		while (history[y] && y < HISTORY_SIZE)
			y++;
	history[y] = ft_strdup(line);
	ft_putstr_fd(history[y], hist_fd);
}

static int	get_nb_of_rows(t_hist *hist)
{
	int		fd;
	char	*line;

	hist->rows = 0;
	fd = open(".history.txt", O_RDONLY, 0777);
	if (fd == -1)
		handle_error("ERROR: Failed to open '.history' file", 1);
	line = get_next_line(fd);
	if (line)
	{
		while (line)
		{
			hist->rows++;
			free(line);
			line = get_next_line(fd);
		}
		printf("rows = %d\n", hist->rows);
		if (close(fd) == -1)
			handle_error("Error: Failed to close '.history.txt' file", 1);
		return (1);
	}
	return (0);
}

void	get_old_history(t_hist *hist)
{
	int		i;
	char	*line;

	i = -1;
	hist->hist_fd = open(".history.txt", O_RDWR | O_APPEND, 0777);
	if (hist->hist_fd == -1)
		handle_error("ERROR: Failed to open '.history' file", 1);
	if (get_nb_of_rows(hist))
	{
		if (hist->rows > HISTORY_SIZE)
			while (++i < hist->rows - HISTORY_SIZE)
				get_next_line(hist->hist_fd);
		i = -1;
		while (++i < HISTORY_SIZE)
			free(hist->history[i]);
		init_history(hist->history);
		i = -1;
		line = get_next_line(hist->hist_fd);
		while (line && ++i < HISTORY_SIZE)
		{
			hist->history[i] = ft_strdup(line);
			line = get_next_line(hist->hist_fd);
		}
	}
	free(line);
}

// we initialize the history array with NULL for security
void	init_history(char **history)
{
	int	i;

	i = -1;
	while (++i < HISTORY_SIZE)
		history[i] = NULL;
}

/* check history file to clear it 
if it has a size bigger than the max history size */

void	clear_history_file(t_hist *hist)
{
	int		fd;

	fd = 0;
	if (get_nb_of_rows(hist))
	{
		if (hist->rows >= HISTORY_SIZE)
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
