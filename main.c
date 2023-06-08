/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykifadji <ykifadji@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 09:54:06 by mkerkeni          #+#    #+#             */
/*   Updated: 2023/06/08 09:31:38 by ykifadji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	t_data				cmd;
	struct sigaction	sig;
	//char		**args;
	char		*line;
	 
	(void)av;
	if (ac != 1)
		handle_error("ERROR: Wrong number of arguments\n", 0);
	ft_bzero(&sig, sizeof(sig));
	sig.sa_flags = SA_RESTART | SA_NODEFER;
	sig.sa_sigaction = signal_handler;
	sigaction(SIGINT, &sig, NULL);
	while(1)
	{
		line = readline("minishell$ ");
		parsing(&cmd, line);
		add_history(line);
		cmd.cmd_line = line;
		cmd.env = env;
		//args = get_env_vars(cmd);
		//print_str_of_str(args);
	}
	return (EXIT_SUCCESS);
}
