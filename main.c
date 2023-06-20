/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerkeni <mkerkeni@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 09:54:06 by mkerkeni          #+#    #+#             */
/*   Updated: 2023/06/20 09:26:47 by mkerkeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	(void)av;
	(void)env;
	g_sh.env = env;
	g_sh.x = 0;
	init_history(g_sh.history);
	if (ac != 1)
		handle_error("ERROR: Wrong number of arguments\n", 1);
	clear_history_file();
	get_old_history();
	while (1)
	{
		g_sh.line = readline("minishell$ ");
		if (!g_sh.line)
		{
			printf("exit\n");
			exit(1);
		}
		add_history(g_sh.line);
		add_line_to_history();
		tokenize_line();
		get_token_type();
		//free(g_sh.line);
		//free(g_sh.var_line);
	}	
	return (EXIT_SUCCESS);
}
