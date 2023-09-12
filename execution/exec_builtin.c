/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerkeni <mkerkeni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 15:03:13 by mkerkeni          #+#    #+#             */
/*   Updated: 2023/09/12 10:28:28 by mkerkeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exec_builtin(char **builtin)
{
	if (!ft_strncmp(builtin, "echo", ft_strlen(builtin)))
		built_echo(builtin);
	else if (!ft_strncmp(builtin, "exit", ft_strlen(builtin)))
		built_exit(builtin);
	else if (!ft_strncmp(builtin, "cd", ft_strlen(builtin)))
		built_cd(builtin);
	else if (!ft_strncmp(builtin, "pwd", ft_strlen(builtin)))
		built_pwd(builtin);
	else if (!ft_strncmp(builtin, "export", ft_strlen(builtin)))
		built_export(builtin);
	else if (!ft_strncmp(builtin, "unset", ft_strlen(builtin)))
		built_unset(builtin);
	else if (!ft_strncmp(builtin, "env", ft_strlen(builtin)))
		built_env(builtin);
}

int	check_env_builtin(char *cmd)
{
	if (!ft_strncmp(cmd, "export", ft_strlen(cmd)))
	{
		if (!ft_strncmp(cmd, "export", ft_strlen("export")))
			return (1);
	}
	else if (!ft_strncmp(cmd, "unset", ft_strlen(cmd)))
	{
		if (!ft_strncmp(cmd, "unset", ft_strlen("unset")))
			return (1);
	}
	else if (!ft_strncmp(cmd, "env", ft_strlen(cmd)))
	{
		if (!ft_strncmp(cmd, "env", ft_strlen("env")))
			return (1);
	}
	return (0);
}

int	is_builtin(char *cmd)
{
	if (!ft_strncmp(cmd, "echo", ft_strlen(cmd)))
	{
		if (!ft_strncmp(cmd, "echo", ft_strlen("echo")))
			return (1);
	}
	else if (!ft_strncmp(cmd, "cd", ft_strlen(cmd)))
	{
		if (!ft_strncmp(cmd, "cd", ft_strlen("cd")))
			return (1);
	}
	else if (!ft_strncmp(cmd, "pwd", ft_strlen(cmd)))
	{
		if (!ft_strncmp(cmd, "pwd", ft_strlen("pwd")))
			return (1);
	}
	else if (!ft_strncmp(cmd, "exit", ft_strlen(cmd)))
	{
		if (!ft_strncmp(cmd, "exit", ft_strlen("exit")))
			return (1);
	}
	else if (check_env_builtin(cmd))
		return (1);
	return (0);
}
