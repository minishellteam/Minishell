/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerkeni <mkerkeni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 09:54:06 by mkerkeni          #+#    #+#             */
/*   Updated: 2023/09/29 15:22:09 by mkerkeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_vars(char *line, t_vars *var, int x)
{
	free(line);
	if (x == 1)
		free_structures(var->cmd, var->pipe_nb);
	free_list_input(var->data, var->pipe_nb, 0);
	free_list(&(var->toks), 0);
	free(var);
}

static void	init_var(t_vars *var, t_data *sh)
{
	var->toks = NULL;
	var->token = NULL;
	var->data = NULL;
	var->bool = 0;
	var->my_env = sh->myenv;
}

static t_vars	*readline_loop(t_vars *var, char *line, t_data *sh)
{
	while (1)
	{
		var = (t_vars *)ft_malloc(sizeof(t_vars));
		init_var(var, sh);
		line = readline("minishell$ ");
		if (!line)
		{
			printf("exit\n");
			free_vars(line, var, 0);
			exit(EXIT_SUCCESS);
		}
		if (*line)
			add_history(line);
		if (tokenize_line(line, var))
			free_vars(line, var, 0);
		else if (get_cmd_infos(var))
			free_vars(line, var, 0);
		else if (create_processes(var, sh))
			free_vars(line, var, 1);
		else
			free_vars(line, var, 1);
	}
	return (var);
}

int	main(int ac, char **av, char **env)
{
	static char	*line;
	t_vars		*var;
	t_data		sh;
	//struct sigaction	sig;
	// t_data			cmd;

	(void)av;
	set_exit_status(EXIT_SUCCESS);
	var = NULL;
	if (ac != 1)
		handle_error("ERROR: Wrong number of arguments\n", 1);
	sh.env = env;
	my_env(&sh);
	exp_env(&sh);
	var = readline_loop(var, line, &sh);
	// ft_bzero(&sig, sizeof(sig));
	// sig.sa_flags = SA_RESTART | SA_NODEFER;
	// sig.sa_sigaction = signal_handler;
	// sigaction(SIGINT, &sig, NULL);
	return (EXIT_SUCCESS);
}
