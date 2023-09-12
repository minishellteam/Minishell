/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerkeni <mkerkeni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 12:35:31 by mkerkeni          #+#    #+#             */
/*   Updated: 2023/09/12 10:28:54 by mkerkeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*get_cmd_path(t_vars *var, char *path)
{
	char	**splitted_paths;
	char	*cmd_path;
	char	*test_cmd_path;
	int		i;

	i = -1;
	splitted_paths = ft_split(path, ':');
	while (splitted_paths[++i])
	{
		test_cmd_path = ft_strjoingnl(splitted_paths[i], "/", 0);
		cmd_path = ft_strjoingnl(test_cmd_path, var->cmd->args[0], 0);
		if (access(cmd_path, X_OK) == 0)
			return (cmd_path);
		free(cmd_path);
	}
	free(splitted_paths);
	return (NULL);
}

char	*get_path(t_vars *var)
{
	char	*path;
	int		i;

	i = -1;
	path = NULL;
	while (var->my_env[++i])
	{
		if (ft_strnstr(var->my_env[i], "PATH=/home", ft_strlen(var->my_env[i])))
		{
			path = var->my_env[i] + 5;
			break ;
		}
	}
	return (path);
}

int	exec_cmd(t_vars *var)
{
	char	**cmds;
	char	*path;
	char	*cmd_path;

	cmds = var->cmd[0].args;
	path = get_path(var);
	if (is_builtin(cmds[0]))
		exec_builtin(var->cmd[0]);
	else
	{
		cmd_path = get_cmd_path(var, path);
		printf("cmd_path = %s\n", cmd_path);
		if (!cmd_path)
		{
			get_error_message(cmds[0], 4);
			return (1);
		}
		cmds[0] = cmd_path;
		if (execve(cmds[0], cmds, var->my_env) == -1)
		{
			perror("minishell: ");
			return (1);
		}
	}
	return (0);
}
