/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerkeni <mkerkeni@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 09:54:06 by mkerkeni          #+#    #+#             */
/*   Updated: 2023/06/11 17:04:07 by mkerkeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	(void)av;
	(void)env;
	g_sh.env = env;
	init_history(g_sh.history);
	if (ac != 1)
		handle_error("ERROR: Wrong number of arguments\n", 1);
	clear_history_file(&g_sh);
	get_old_history(&g_sh);
	while (1)
	{
		g_sh.line = readline("minishell$ ");
		if (!g_sh.line)
		{
			printf("exit\n");
			exit(1);
		}
		add_history(g_sh.line);
		tokenize_line(g_sh.line);
		//get_token_type();
		add_line_to_history(&g_sh);
		g_sh.var_line = get_value_vars(g_sh);
		printf("%s\n", g_sh.var_line);
		free(g_sh.line);
		free(g_sh.var_line);
	}	
	return (EXIT_SUCCESS);
}
