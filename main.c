/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerkeni <mkerkeni@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 09:54:06 by mkerkeni          #+#    #+#             */
/*   Updated: 2023/06/08 16:11:04 by mkerkeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void add_line_to_history(const char* line, char** history, int* history_size, int max_history_size)
{
	int	i;

	i = 0;
	if (*history_size >= max_history_size) 
	{
		free(history[0]);
		while(++i < max_history_size) 
		history[i - 1] = history[i];
		--(*history_size);
    }
	history[*history_size] = strdup(line);
	++(*history_size);
}

int	main(int ac, char **av, char **env)
{
	t_data	cmd;
	char	*line;
	char	*history[1000];
	int		history_size;

	(void)av;
	(void)env;
	line = NULL;
	if (ac != 1)
		handle_error("ERROR: Wrong number of arguments\n", 1);
	while (1)
	{
		line = readline("minishell$ ");
		add_history(line);
		add_line_to_history(line, history, history_size, 1000);
		cmd.line = line;
		cmd.env = env;
		cmd.var_line = get_value_vars(cmd);
		free(line);
		free(cmd.var_line);
	}	
	return (EXIT_SUCCESS);
}
