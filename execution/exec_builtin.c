/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerkeni <mkerkeni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 15:03:13 by mkerkeni          #+#    #+#             */
/*   Updated: 2023/09/13 22:33:57 by mkerkeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exec_builtin(t_data *sh)
{
	if (!ft_strncmp(sh->cmds[0], "echo", ft_strlen(builtin)))
		built_echo(sh);
	else if (!ft_strncmp(sh->cmds[0], "exit", ft_strlen(builtin)))
		built_exit(sh);
	else if (!ft_strncmp(sh->cmds[0], "cd", ft_strlen(builtin)))
		built_cd(sh);
	else if (!ft_strncmp(sh->cmds[0], "pwd", ft_strlen(builtin)))
		built_pwd(sh);
	else if (!ft_strncmp(sh->cmds[0], "export", ft_strlen(builtin)))
		built_export(sh);
	else if (!ft_strncmp(sh->cmds[0], "unset", ft_strlen(builtin)))
		built_unset(sh);
	else if (!ft_strncmp(sh->cmds[0], "env", ft_strlen(builtin)))
		built_env(sh);
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
