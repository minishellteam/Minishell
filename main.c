/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerkeni <mkerkeni@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 09:54:06 by mkerkeni          #+#    #+#             */
/*   Updated: 2023/06/11 11:07:08 by mkerkeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	t_data	cmd;
	char	*history[HISTORY_SIZE];

	(void)av;
	(void)env;
	cmd.line = NULL;
	cmd.line_pos = 0;
	cmd.history = history;
	init_history(history);
	if (ac != 1)
		handle_error("ERROR: Wrong number of arguments\n", 1);
	clear_history_file(&cmd);
	get_old_history(&cmd);
	while (1)
	{
		cmd.line = readline("minishell$ ");
		add_history(cmd.line);
		add_line_to_history(&cmd);
		print_str_of_str(cmd.history, HISTORY_SIZE);
		cmd.env = env;
		cmd.var_line = get_value_vars(cmd);
		free(cmd.line);
		free(cmd.var_line);
	}	
	return (EXIT_SUCCESS);
}
