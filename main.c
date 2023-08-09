/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerkeni <mkerkeni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 09:54:06 by mkerkeni          #+#    #+#             */
/*   Updated: 2023/08/10 00:00:25 by mkerkeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	static char	*line;
	//t_hist		*hist;
	//struct sigaction	sig;
	// t_data			cmd;

	(void)av;
	(void)env;
//	hist = (t_hist *)malloc(sizeof(t_hist));
	//hist->hist_fd = 0;
	if (ac != 1)
		handle_error("ERROR: Wrong number of arguments\n", 1);
	//init_history(hist->history);
	//clear_history_file(hist);
	//get_old_history(hist);
	// ft_bzero(&sig, sizeof(sig));
	// sig.sa_flags = SA_RESTART | SA_NODEFER;
	// sig.sa_sigaction = signal_handler;
	// sigaction(SIGINT, &sig, NULL);
	while (1)
	{
		line = readline("minishell$ ");
		if (!line)
		{
			free(line);
			//free(hist->history);
			//free(hist);
			printf("exit\n");
			exit(1);
		}
		if (*line)
			add_history(line);
	//	add_line_to_history(line, hist->history, hist->hist_fd);
		tokenize_line(line);
		//ft_builts(&cmd);
	}
	return (EXIT_SUCCESS);
}
