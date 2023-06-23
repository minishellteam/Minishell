/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykifadji <ykifadji@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 09:39:01 by ykifadji          #+#    #+#             */
/*   Updated: 2023/06/23 08:05:25 by ykifadji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_tab(t_data *cmd)
{
	int	j;

	j = -1;
	while (cmd->export->env[++j] && cmd->export->exp[j])
	{
		if (cmd->export->env[j])
			free(cmd->export->env[j]);
		if (cmd->export->exp[j])
			free(cmd->export->exp[j]);
	}
}

void	built_pwd(t_data *cmd)
{
	char	buffer[BUFF_SIZE];

	if (!ft_strncmp(cmd->cmds[0], "pwd", 3) && ft_strlen(cmd->cmds[0]) == 3)
	{
		if (getcwd(buffer, BUFF_SIZE))
			printf("%s\n", buffer);
		else
			handle_error("minishell: ", 1);
	}
}

void	built_cd(t_data *cmd)
{
	char	**tmp;

	if (!ft_strncmp(cmd->cmds[0], "cd", 2))
	{
		tmp = ft_split(cmd->line, ' ');
		if (chdir(tmp[1]) == -1)
			handle_error("minishell$ ", 1);
	}
}

void	built_env(t_data *cmd)
{
	int	i;

	i = -1;
	if (!ft_strncmp(cmd->cmds[0], "env", 3))
	{
		while (cmd->env[++i])
			printf("%s\n", cmd->env[i]);
	}
}
