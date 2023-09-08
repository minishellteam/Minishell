/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerkeni <mkerkeni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 09:54:06 by mkerkeni          #+#    #+#             */
/*   Updated: 2023/09/08 12:55:00 by mkerkeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_vars(char *line, t_vars *var, int x)
{
	free(line);
	if (x == 1)
		free_structures(var->cmd, var->pipe_nb);
	free_list_input(var->data, 0);
	free_list(&(var->toks), 0);
	free(var);
}

static void	init_var(t_vars *var, char **env)
{
	var->toks = NULL;
	var->token = NULL;
	var->data = NULL;
	var->my_env = env;
}

static void	free_and_exit(char *line, t_vars *var, int x)
{
	free_vars(line, var, x);
	exit(EXIT_FAILURE);
}

t_vars	*readline_loop(t_vars *var, char *line, char **env)
{
	while (1)
	{
		var = (t_vars *)malloc(sizeof(t_vars));
		init_var(var, env);
		line = readline("minishell$ ");
		if (!line)
		{
			printf("exit\n");
			free_and_exit(line, var, 0);
		}
		if (*line)
			add_history(line);
		if (tokenize_line(line, var))
			free_and_exit(line, var, 0);
		if (get_cmd_infos(var))
			free_and_exit(line, var, 0);
		if (create_processes(var))
			free_and_exit(line, var, 1);
		free_vars(line, var, 1);
		//ft_builts(&cmd);
	}
	return (var);
}

int	main(int ac, char **av, char **env)
{
	static char	*line;
	t_vars		*var;
	//struct sigaction	sig;
	// t_data			cmd;

	(void)av;
	var = NULL;
	if (ac != 1)
		handle_error("ERROR: Wrong number of arguments\n", 1);
	var = readline_loop(var, line, env);
	// ft_bzero(&sig, sizeof(sig));
	// sig.sa_flags = SA_RESTART | SA_NODEFER;
	// sig.sa_sigaction = signal_handler;
	// sigaction(SIGINT, &sig, NULL);
	return (EXIT_SUCCESS);
}
