/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_echo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykifadji <ykifadji@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 11:22:52 by ykifadji          #+#    #+#             */
/*   Updated: 2023/06/23 07:47:10 by ykifadji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_echo(t_data *cmd, int bool)
{
	cmd->j--;
	while (cmd->echo[++cmd->j])
	{
		printf("%s", cmd->echo[cmd->j]);
		if (cmd->echo[cmd->j + 1])
			printf(" ");
	}
	if (bool == 0)
		printf("\n");
}

static int	check_n(t_data *cmd)
{
	int	bool;

	cmd->j = 0;
	bool = 0;
	while (cmd->echo[++cmd->j])
	{
		if (cmd->echo[cmd->j][0] == '-' && ft_strlen(cmd->echo[cmd->j]) > 1)
		{
			cmd->i = 0;
			while (cmd->echo[cmd->j][++cmd->i])
				if (cmd->echo[cmd->j][cmd->i] != 'n')
					return (bool);
			bool = 1;
		}
		else
			return (bool);
	}
	return (bool);
}

void	built_echo(t_data *cmd)
{
	int	bool;

	cmd->j = 0;
	if (!ft_strncmp(cmd->cmds[cmd->j], "echo", 4) \
		&& cmd->cmds[cmd->j][4] != ' ')
	{
		printf("\n");
		return ;
	}
	cmd->echo = ft_split(cmd->cmds[cmd->j], ' ');
	if (check_n(cmd) == 1)
		bool = 1;
	else
		bool = 0;
	print_echo(cmd, bool);
}
