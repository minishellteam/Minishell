/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerkeni <mkerkeni@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 16:03:10 by mkerkeni          #+#    #+#             */
/*   Updated: 2023/06/09 15:06:13 by mkerkeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_line_to_history(t_data cmd)
{
	int		y;
	int		i;
	
	y = 0;
	i = 0;
	cmd.line = ft_strjoin(cmd.line, "\n");
	if (cmd.history[HISTORY_SIZE - 1])
	{
		cmd.history[0] = NULL;
		free(cmd.history[0]);
		i = 0;
		while (++i < HISTORY_SIZE)
			cmd.history[i - 1] = cmd.history[i];
		y = HISTORY_SIZE - 1;
	}
	else
		while (cmd.history[y] && y < HISTORY_SIZE)
			y++;
	cmd.history[y] = ft_strdup(cmd.line);
}

void	init_history(char **history)
{
	int	i;

	i = -1;
	while (++i < HISTORY_SIZE)
		history[i] = NULL;
}

void	save_history_in_file(t_data cmd)
{
	int	y;

	y = -1;
	print_str_of_str(cmd.history, HISTORY_SIZE);
	while(++y < 10)
		ft_putstr_fd(cmd.history[y], cmd.hist_fd);
}

static int	get_nb_of_rows(t_data cmd)
{
	int		fd;
	char	*line;
	int		rows;

	rows = 0;
	fd = open(".history.txt", O_RDONLY, 0777);
	if (fd == -1)
		handle_error("ERROR: Failed to open '.history.txt' file", 1);
	line = get_next_line(fd); 
	if (line)
	{
		while (line)
		{
			rows++;
			free(line);
			line = get_next_line(fd); 
		}
		cmd.rows = rows;
		if (close(fd) == -1)
			handle_error("Error: Failed to close '.history.txt' file", 1);
		printf("rows = %d\n", rows);
		return(1);
	}
	return (0);
}

void	get_old_history(t_data cmd)
{
	int		fd;
	int		i;
	int		j;
	char	*line;

	i = -1;
	j = -1;
	if (get_nb_of_rows(cmd))
	{
		fd = open(".history.txt", O_RDWR | O_APPEND, 0777);
		if (fd == -1)
			handle_error("ERROR: Failed to open '.history.txt' file", 1);
		cmd.hist_fd = fd;
		while (++i < cmd.rows - HISTORY_SIZE)
			get_next_line(fd);
		while (++j < HISTORY_SIZE)
			free(cmd.history[j]);
		init_history(cmd.history);
		j = -1;
		while (++j < HISTORY_SIZE)
		{
			line = get_next_line(fd);
			cmd.history[j] = ft_strdup(line);
		}
	}
}
