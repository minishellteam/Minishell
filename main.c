/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykifadji <ykifadji@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 09:54:06 by mkerkeni          #+#    #+#             */
/*   Updated: 2023/06/16 11:12:20 by ykifadji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	t_data				cmd;
	struct sigaction	sig;
	char		*line;
 
	(void)av;
	(void)env;
	line = NULL;
	if (ac != 1)
		handle_error("ERROR: Wrong number of arguments\n", 1);
	ft_bzero(&sig, sizeof(sig));
	sig.sa_flags = SA_RESTART | SA_NODEFER;
	sig.sa_sigaction = signal_handler;
	sigaction(SIGINT, &sig, NULL);
	while (1)
	{
		line = readline("minishell$ ");
		parsing(&cmd, line);
		add_history(line);
		cmd.line = line;
		cmd.env = env;
		ft_builts(&cmd);
		free(line);
	}
	return (EXIT_SUCCESS);
}
