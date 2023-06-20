/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerkeni <mkerkeni@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 09:54:06 by mkerkeni          #+#    #+#             */
/*   Updated: 2023/06/20 14:55:52 by mkerkeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	struct sigaction	sig;
	// t_data			cmd;

	(void)av;
	(void)env;
	g_sh.env = env;
	g_sh.x = 0;
	init_history(g_sh.history);
	if (ac != 1)
		handle_error("ERROR: Wrong number of arguments\n", 1);
	clear_history_file();
	get_old_history();
	ft_bzero(&sig, sizeof(sig));
	sig.sa_flags = SA_RESTART | SA_NODEFER;
	sig.sa_sigaction = signal_handler;
	sigaction(SIGINT, &sig, NULL);
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
		parse_tokens();
		//ft_builts(&cmd);
		//free(g_sh.line);
		//free(g_sh.var_line);
	}
	return (EXIT_SUCCESS);
}
