/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerkeni <mkerkeni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 09:54:06 by mkerkeni          #+#    #+#             */
/*   Updated: 2023/10/09 14:19:31 by mkerkeni         ###   ########.fr       */
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
	var->sh = sh;
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

static void	check_args(int ac, char **av, char **env)
{
	if (ac != 1)
	{
		get_error_message(av[1], 3);
		if (ac > 2)
			exit(127);
	}
	else if (!env[0])
		ft_putstr_fd("minishell: the environment is empty\n", 2);
	exit(EXIT_FAILURE);
}

int	main(int ac, char **av, char **env)
{
	static char	*line;
	t_vars		*var;
	t_data		sh;
	//struct sigaction	sig;

	set_exit_status(EXIT_SUCCESS);
	var = NULL;
	check_args(ac, av, env);
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
