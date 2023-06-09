/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerkeni <mkerkeni@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 09:54:06 by mkerkeni          #+#    #+#             */
/*   Updated: 2023/06/09 14:05:16 by mkerkeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	t_data	cmd;
	char	*line;
	char	*history[HISTORY_SIZE];

	(void)av;
	(void)env;
	line = NULL;
	cmd.history = history;
	init_history(history);
	if (ac != 1)
		handle_error("ERROR: Wrong number of arguments\n", 1);
	while (1)
	{
		line = readline("minishell$ ");
		add_history(line);
		cmd.line = line;
		get_old_history(cmd);
		add_line_to_history(cmd);
		save_history_in_file(cmd);
		cmd.env = env;
		cmd.var_line = get_value_vars(cmd);
		free(line);
		free(cmd.var_line);
	}	
	return (EXIT_SUCCESS);
}
