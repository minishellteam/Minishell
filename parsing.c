/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykifadji <ykifadji@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 10:31:22 by ykifadji          #+#    #+#             */
/*   Updated: 2023/06/07 11:48:28 by ykifadji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_chevron(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '>' && str[i + 2] == '>')
			handle_error("minishell: syntax error near unexpected token `<'\n", \
				0);
	}
}

void	parsing(t_data *cmd, char *line)
{
	int	j;
	int	i;

	cmd->cmds = ft_split(line, '|');
	j = -1;
	while (cmd->cmds[++j])
	{
		i = -1;
		while (cmd->cmds[j][++i])
		{
			if (cmd->cmds[j][i] == '>')
				check_chevron(cmd->cmds[j]);
		}
	}
}
