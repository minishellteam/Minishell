/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykifadji <ykifadji@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 14:09:27 by ykifadji          #+#    #+#             */
/*   Updated: 2023/06/23 07:58:05 by ykifadji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	arg_error(t_data *cmd)
{
	char	*new;
	int		i;
	int		j;

	i = 4;
	while (cmd->line[++i])
	{
		if (!ft_isdigit(cmd->line[i]))
		{
			new = malloc(sizeof(char) * (ft_strlen(cmd->line) - 3));
			i = 4;
			j = -1;
			while (cmd->line[++i] && cmd->line[i] != ' ')
				new[++j] = cmd->line[i];
			new[j + 1] = '\0';
			printf("minishell: exit: %s: numeric argument required\n",
				new);
			free(new);
			new = NULL;
			return ;
		}
	}
}

void	built_exit(t_data *cmd)
{
	int	i;

	i = 4;
	cmd->line = ft_strtrim(cmd->line, " ");
	if (!ft_strncmp(cmd->line, "exit", 4) && !ft_strchr(cmd->line, '|'))
	{
		if (ft_strlen(cmd->line) > 4 && cmd->line[4] != ' ')
			return ;
		printf("exit\n");
		if (ft_strlen(cmd->line) > 4)
			arg_error(cmd);
		if (ft_strlen(cmd->line) > 4 && cmd->line[5] == '1')
			exit(EXIT_FAILURE);
		else if (ft_strlen(cmd->line) > 4 && cmd->line[5] == '0')
			exit(EXIT_SUCCESS);
		exit(EXIT_SUCCESS);
	}
}

void	ft_builts(t_data *cmd)
{
	built_exit(cmd);
	built_echo(cmd);
	built_pwd(cmd);
	built_cd(cmd);
	built_export(cmd);
	built_env(cmd);
}
