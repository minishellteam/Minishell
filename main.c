/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerkeni <mkerkeni@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 09:54:06 by mkerkeni          #+#    #+#             */
/*   Updated: 2023/06/08 10:32:07 by mkerkeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	t_data	cmd;
	char		*args;
	char		*line;

	(void)av;
	if (ac != 1)
		handle_error("ERROR: Wrong number of arguments\n", 1);
	while (1)
	{
		line = readline("minishell$ ");
		add_history(line);
		cmd.line = line;
		cmd.env = env;
		args = get_value_vars(cmd);
	}
	return (EXIT_SUCCESS);
}
