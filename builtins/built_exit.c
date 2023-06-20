/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerkeni <mkerkeni@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 14:09:27 by ykifadji          #+#    #+#             */
/*   Updated: 2023/06/20 09:59:06 by mkerkeni         ###   ########.fr       */
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
	char	buffer[BUFF_SIZE];
	char	**tmp;

	built_exit(cmd);
	built_echo(cmd);
	if (!ft_strncmp(cmd->cmds[0], "pwd", 3) && ft_strlen(cmd->cmds[0]) == 3)
	{
		if (getcwd(buffer, BUFF_SIZE))
			printf("%s\n", buffer);
		else
			handle_error("minishell: ", 1);
	}
	if (!ft_strncmp(cmd->cmds[0], "cd", 2))
	{
		tmp = ft_split(cmd->line, ' ');
		if (chdir(tmp[1]) == -1)
			handle_error("minishell$ ", 1);
	}
	//built_export(cmd);
}
