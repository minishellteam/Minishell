/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykifadji <ykifadji@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 09:54:06 by mkerkeni          #+#    #+#             */
/*   Updated: 2023/09/12 11:05:30 by ykifadji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	struct sigaction	sig;
	t_data			sh;

	(void)av;
	(void)env;
	sh.env = env;
	sh.x = 0;
	//init_history(sh.history);
	if (ac != 1)
		handle_error("ERROR: Wrong number of arguments\n", 1);
	//clear_history_file();
	//get_old_history();
	ft_bzero(&sig, sizeof(sig));
	sig.sa_flags = SA_RESTART | SA_NODEFER;
	sig.sa_sigaction = signal_handler;
	sigaction(SIGINT, &sig, NULL);
	my_env(&sh);
	while (1)
	{
		sh.line = readline("minishell$ ");
		if (!sh.line)
		{
			printf("exit\n");
			exit(1);
		}
		if (*sh.line)
			add_history(sh.line);
		// add_line_to_history();
		// tokenize_line();
		// print_list(sh.toks, 1);
		// parse_tokens();
		// printf("--------------\n");
		// print_list(sh.toks, 1);
		ft_builts(&sh);
		// free(sh.line);
		// free(sh.var_line);
	}
	return (EXIT_SUCCESS);
}
