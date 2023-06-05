/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerkeni <mkerkeni@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 09:54:06 by mkerkeni          #+#    #+#             */
/*   Updated: 2023/06/02 14:29:29 by mkerkeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	t_command	cmd;
	char		**args;
	char		*line;
	
	(void)av;
	if (ac != 1)
		ft_error("ERROR: Wrong number of arguments\n");
	while(1)
	{
		line = readline("minishell$ ");
		add_history(line);
		cmd.cmd_line = line;
		cmd.env = env;
		args = get_env_vars(cmd);
		print_str_of_str(args);
	}
	return (EXIT_SUCCESS);
}
